namespace BuildMaster
{
    class RebuildDataAction : IAction
    {
        public string Name => "rebuilddata";

        public static RebuildDataAction Create() { return new RebuildDataAction(); }

        public bool Perform(Config config)
        {
            var cleanAction = new CleanAction();
            if (!cleanAction.Perform(config))
                return false;

            var buildDataAction = new BuildDataAction();
            if (!buildDataAction.Perform(config))
                return false;

            return true;
        }
    }
}
