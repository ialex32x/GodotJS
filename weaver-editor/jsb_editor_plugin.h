#ifndef GODOTJS_EDITOR_PLUGINS_H
#define GODOTJS_EDITOR_PLUGINS_H

#include "jsb_editor_macros.h"
#include "scene/gui/dialogs.h"
#include "editor/editor_plugin.h"

namespace jsb
{
    enum ECategoryHint : uint8_t
    {
        CH_JAVASCRIPT = 1 << 0,
        CH_TYPESCRIPT = 1 << 1,
        CH_MISC = 1 << 2,

        // only write file if not existed since some files would be modified in projects, such as package.json, by users
        CH_CREATE_ONLY = 1 << 3,

        CH_OPTIONAL = 1 << 7,
    };

    struct InstallFileInfo
    {
        String source_name;
        String target_dir;

        // ECategoryHint
        uint8_t hint;
    };
}

class InstallGodotJSPresetConfirmationDialog : public ConfirmationDialog
{
	GDCLASS(InstallGodotJSPresetConfirmationDialog, ConfirmationDialog);

public:
    Vector<String> source_names_;
};

class GodotJSEditorPlugin : public EditorPlugin
{
    GDCLASS(GodotJSEditorPlugin, EditorPlugin)

private:
    Vector<jsb::InstallFileInfo> install_files_;
    InstallGodotJSPresetConfirmationDialog* confirm_dialog_;

protected:
    static void _bind_methods();

    void _notification(int p_what);
    void _on_menu_pressed(int p_what);
    void _on_confirm_overwrite();
    static Error write_file(const jsb::InstallFileInfo& p_file);

public:
    GodotJSEditorPlugin();
    virtual ~GodotJSEditorPlugin() override;

    void try_install_ts_project();
    bool verify_ts_project() const;

    static void generate_godot_dts();
    static void install_ts_project(const Vector<jsb::InstallFileInfo>& p_files);

    /**
     * return true if everything is identical to the expected version.
     * otherwise return false with changed files in `r_modified`.
     */
    static bool verify_files(const Vector<jsb::InstallFileInfo>& p_files, bool p_verify_content, Vector<String>* r_modified);
    static bool verify_file(const jsb::InstallFileInfo& p_file, bool p_verify_content);

    static void on_successfully_installed();

    static void load_editor_entry_module();
};

#endif
