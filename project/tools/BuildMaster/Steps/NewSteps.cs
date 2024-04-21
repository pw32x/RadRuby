﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace BuildMaster
{
    class NewSteps
    {
        public static bool BuildCode(Config config)
        {
            Console.WriteLine("Step: Build code:");

            return BuildProject(config);
        }

        public static void CleanOutputFolder(Config config)
        {
            Utils.DeleteAllFilesRecursive(config.CompilationSettings.OutFolder);
        }

        public static void CleanExportFolder(Config config)
        {
            var toolExportFolders = config.GetToolExportFolders();

            foreach (var toolExportFolder in toolExportFolders)
            {
                Utils.DeleteAllFiles(toolExportFolder);
            }
        }

        private static bool BuildProject(Config config)
        {
            // Create a new process start info
            ProcessStartInfo psi = new ProcessStartInfo
            {
                FileName = "..\\..\\..\\sgdk200\\bin\\make.exe", // Use the command prompt
                RedirectStandardInput = true,
                RedirectStandardError = true,
                UseShellExecute = false,
                Arguments = "-f " + config.GetSetting("MakefilePath") + " TARGET=\"" + config.ProjectName + "\"",
                //CreateNoWindow = !Debugger.IsAttached
            };

            // Start the process
            Process process = new Process { StartInfo = psi };
            process.Start();

            // Get the process's input stream
            StreamWriter sw = process.StandardInput;
            StreamReader errorReader = process.StandardError; 

            // Close the input stream to indicate the end of input
            sw.Close();

            var errorString = errorReader.ReadToEnd();

            // Wait for the process to complete
            process.WaitForExit();

            // Display the exit code
            //Console.WriteLine("Exit Code: " + process.ExitCode);

            // Close the process
            process.Close();

            bool containsError = ProcessErrorString(errorString, config);

            return !containsError;
        }

        static (string, int, string) ExtractErrorInfo(string line)
        {
            // Define the pattern with capturing groups
            string pattern = @"^(.*):(\d+):";

            // Match the pattern
            Match match = Regex.Match(line, pattern);

            // Check if the string matches the pattern
            if (match.Success)
            {
                // Extract the path and line number from capturing groups
                string filePath = match.Groups[1].Value;
                int lineNumber = int.Parse(match.Groups[2].Value);

                string restOfString = line.Substring(match.Length).Trim();

                return (filePath, lineNumber, restOfString);
            }

            return ("", 0, line);
        }

        private static bool ProcessErrorString(string errorString, Config config)
        {
            bool containsError = false;

            if (!String.IsNullOrEmpty(errorString))
            {
                string[] lines = errorString.Split(new[] { Environment.NewLine }, StringSplitOptions.None);

                foreach (var line in lines)
                {
                    var (filePath, lineNumber, message) = ExtractErrorInfo(line);

                    if (string.IsNullOrEmpty(message))
                        continue;

                    if (!containsError)
                    {
                        containsError = message.ToLower().Contains("error");
                    }

                    Console.WriteLine(line);
                }
            }

            return containsError;
        }
    }
}
