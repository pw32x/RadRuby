namespace BuildMaster
{
    class BuildDataAction : IAction
    {
        public string Name => "builddata";

        public static BuildDataAction Create() { return new BuildDataAction(); }

        public bool Perform(Config config)
        {
            Steps.RunAllTools(config);

            return true;
        }
    }
}
