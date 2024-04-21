namespace BuildMaster
{
    class BuildDataAction : IAction
    {
        public string Name => "builddata";

        public static BuildDataAction Create() { return new BuildDataAction(); }

        public bool Perform(Config config)
        {
            Steps.RunAllTools(config);

            //NewSteps.GenerateResourceInfos(config);

            /*
            bool result = Utils.BenchmarkStep(NewSteps.BuildCode, config, "New Build Code");

            if (result && config.GetSetting("CopyToDailyFolder") == "true")
            {
                Steps.CopyToDailyFolder(config);
            }
            */

            return true;
        }
    }
}
