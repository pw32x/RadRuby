using System.Collections.Generic;

namespace BuildMaster
{
    class CompilationSettings
    {
        public CompilationSettings(string outFolder)
        {
            OutFolder = Utils.NormalizePath(outFolder);
        }

        public List<string> Defines { get; } = new();
        public string OutFolder { get; }
    }

}
