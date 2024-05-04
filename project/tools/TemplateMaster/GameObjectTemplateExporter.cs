
using System.Text;

namespace TemplateMaster
{
    internal class GameObjectTemplateExporter
    {
        internal static void Export(GameObjectTemplate gameObjectTemplate, 
                                    string templateName, 
                                    string sourceDestinationPath,
                                    string headerDestinationPath)
        {
            ExportSource(gameObjectTemplate, templateName, sourceDestinationPath);
            ExportHeader(gameObjectTemplate, templateName, headerDestinationPath);
        }

        private static void ExportSource(GameObjectTemplate gameObjectTemplate, string templateName, string sourceDestinationPath)
        {
            var sb = new StringBuilder();

            if (gameObjectTemplate.CustomDataFields.Count > 0)
                sb.AppendLine("#include \"" + templateName + ".h\"");

            sb.AppendLine("#include \"engine\\gameobject_template_types.h\"");
            sb.AppendLine("#include \"engine\\object_types.h\"");
            sb.AppendLine("#include \"engine\\createinfo_types.h\"");
            sb.AppendLine("#include \"client\\generated\\resources.h\"");
            sb.AppendLine();

            // declare the extra resource infos used
            ExportExtraResources(gameObjectTemplate, templateName, sb);

            string gameObjectType = gameObjectTemplate.CustomDataFields.Count == 0 ? "GameObject" : gameObjectTemplate.Name.Replace(" ", "") + "ObjectType";

            string createInfoTypeName = string.IsNullOrEmpty(gameObjectTemplate.CreateInfoType) ? "CreateInfo" : gameObjectTemplate.CreateInfoType;

            // forward declare the init function
            sb.AppendLine("GameObject* " + gameObjectTemplate.InitFunction + "(" + gameObjectType + "* object, const " + createInfoTypeName + "* createInfo);");
            sb.AppendLine();
            ExportGameTemplateStruct(gameObjectTemplate, templateName, sb);

            File.WriteAllText(sourceDestinationPath, sb.ToString());
        }

        private static void ExportHeader(GameObjectTemplate gameObjectTemplate, string templateName, string headerDestinationPath)
        {
            // we only export the custom objct struct for now.
            if (gameObjectTemplate.CustomDataFields.Count == 0) 
                return;

            var sb = new StringBuilder();

            sb.AppendLine("#ifndef " + templateName.ToUpper() + "_INCLUDE_H");
            sb.AppendLine("#define " + templateName.ToUpper() + "_INCLUDE_H");
            sb.AppendLine();
            sb.AppendLine("#include \"engine\\object_types.h\"");
            foreach (var include in gameObjectTemplate.AdditionalIncludes)
            {
                sb.AppendLine("#include \"" + include + "\"");
            }

            sb.AppendLine();
            ExportCustomObjectStruct(gameObjectTemplate, templateName, sb);

            sb.AppendLine();
            sb.AppendLine("#endif");

            File.WriteAllText(headerDestinationPath, sb.ToString());
        }

        private static void ExportCustomObjectStruct(GameObjectTemplate gameObjectTemplate, string templateName, StringBuilder sb)
        {

            // declare the template struct
            sb.AppendLine("typedef struct " + gameObjectTemplate.Name.Replace(" ", "_").ToLower() + "_object");
            sb.AppendLine("{");
            sb.AppendLine("    GAME_OBJECT_FIELDS;");

            foreach (var customDataField in gameObjectTemplate.CustomDataFields)
            {
                sb.AppendLine("    " + customDataField + ";");
            }

            sb.AppendLine("} "  + gameObjectTemplate.Name.Replace(" ", "") + "ObjectType;");
        }

        private static void ExportGameTemplateStruct(GameObjectTemplate gameObjectTemplate, string templateName, StringBuilder sb)
        {

            // declare the template struct
            sb.AppendLine("const GameObjectTemplate " + templateName + " = ");
            sb.AppendLine("{");
            AppendField(gameObjectTemplate.Health, sb, "0", "health");
            AppendField(gameObjectTemplate.Damage, sb, "0", "damage");
            AppendField(gameObjectTemplate.RectLeft, sb, "0", "rect left");
            AppendField(gameObjectTemplate.RectTop, sb, "0", "rect top");
            AppendField(gameObjectTemplate.RectRight, sb, "0", "rect right");
            AppendField(gameObjectTemplate.RectBottom, sb, "0", "rect bottom");
            AppendField("OBJECTTYPE_" + gameObjectTemplate.GameObjectType.ToUpper(), sb, "Error", "object type");

            string resource = "NULL";
            if (!string.IsNullOrEmpty(gameObjectTemplate.Resource))
                resource = "(const Resource*)&" + gameObjectTemplate.Resource;

            AppendField(resource, sb, "Error", "resource");

            string extraResources = "NULL";
            if (gameObjectTemplate.ExtraResources.Count > 0)
            {
                extraResources = templateName + "ExtraResources";
            }

            AppendField(extraResources, sb, "Error", "extra resources");

            string initFunction = gameObjectTemplate.InitFunction;

            if (gameObjectTemplate.CustomDataFields.Count > 0 || !string.IsNullOrEmpty(gameObjectTemplate.CreateInfoType)) 
                initFunction = "(InitObjectFunctionType)" + initFunction;

            AppendField(initFunction, sb, "Error", "init function");

            sb.AppendLine("};");

            static void AppendField(string field, StringBuilder sb, string defaultValue, string description)
            {
                string fieldToUse = field;
                if (string.IsNullOrEmpty(field))
                    fieldToUse = defaultValue;

                sb.AppendLine("    " + fieldToUse + ", // " + description);
            }
        }

        private static void ExportExtraResources(GameObjectTemplate gameObjectTemplate, string templateName, StringBuilder sb)
        {
            if (gameObjectTemplate.ExtraResources.Count == 0)
                return;

            sb.AppendLine("const Resource* " + templateName + "ExtraResources[] = ");
            sb.AppendLine("{");

            foreach (var resource in gameObjectTemplate.ExtraResources)
            {
                sb.AppendLine("    &" + resource + ",");
            }

            sb.AppendLine("};");

            sb.AppendLine();
        }

        internal static void ExportAllHeader(IEnumerable<string> templateNames, 
                                             string destinationFolder)
        {
            var sb = new StringBuilder();

            sb.AppendLine("#ifndef GAMEOBJECT_TEMPLATES_INCLUDE_H");
            sb.AppendLine("#define GAMEOBJECT_TEMPLATES_INCLUDE_H");
            sb.AppendLine();
            sb.AppendLine("#include \"..\\..\\..\\engine\\gameobject_template_types.h\"");
            sb.AppendLine();

            foreach (var templateName in templateNames)
            {
                sb.AppendLine("extern const GameObjectTemplate " + templateName + "_template;");
            }

            sb.AppendLine();
            sb.AppendLine("#endif");

            File.WriteAllText(destinationFolder + "gameobject_templates.h", sb.ToString());
        }
    }
}