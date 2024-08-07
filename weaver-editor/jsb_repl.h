﻿#ifndef GODOTJS_REPL_H
#define GODOTJS_REPL_H
#include "../internal/jsb_console_output.h"
#include "../weaver/jsb_gdjs_lang.h"
#include "scene/gui/box_container.h"

class GodotJSREPL : public HBoxContainer, public jsb::internal::IConsoleOutput
{
    GDCLASS(GodotJSREPL, HBoxContainer)
    struct OutputLine
    {
        String text;
    };

private:
    bool input_submitting_;
    class LineEdit* input_box_;
    class RichTextLabel* output_box_;

    class Button* clear_button_;
    class Button* dts_button_;
    class Button* preset_button_;
    class Label* preset_hint_label_;
    class Button* start_tsc_button_;

    class ItemList* candidate_list_;

    Vector<OutputLine> lines_;
    Vector<String> history_;

private:
    void _update_theme();

protected:
    void _input_submitted(const String& p_text);
    void _input_changed(const String& p_text);
    void _input_gui_input(const Ref<InputEvent> &p_event);
    void _input_focus_exit();
    void _clear_pressed();
    void _generate_dts_pressed();
    void _install_preset_pressed();
    void _start_tsc_pressed();
    void _notification(int p_what);

    void add_string(const String& p_str);
    void add_line(const String& p_line);
    void add_history(const String& p_text);
    jsb::JSValueMove eval_source(const String& p_code);
    String encode_string(const String& p_text);
    void check_install();
    void check_tsc();

public:
    GodotJSREPL();
    virtual ~GodotJSREPL() override;

    void write(jsb::internal::ELogSeverity::Type p_severity, const String& p_text) override;
};
#endif
