/* NAppGUI Hello World */

#include <nappgui.h>

int32_t get_random(void);

typedef struct _app_t App;

struct _app_t
{
    Window *window;
    TextView *text;
    uint32_t clicks;
    Menu *menu;
};

/*---------------------------------------------------------------------------*/

static void i_OnButton(App *app, Event *e)
{
    int32_t res = get_random();
    textview_printf(app->text, "Random: %i \n", res);
    app->clicks += 1;
    unref(e);
}

/*---------------------------------------------------------------------------*/

static Panel *i_panel(App *app)
{
    Panel *panel = panel_create();
    Layout *layout = layout_create(1, 3);
    Layout *layout1 = layout_create(3, 1);        
    Layout *layout2 = layout_create(8, 1);

    
    Label *label = label_create();
    
    Button *button = button_push();
    button_text(button, "Open");
    
    Button *button2 = button_push();
    button_text(button2, "Save");
    
    TextView *text = textview_create();
    textview_editable(text, TRUE);
    label_text(label, "m1m1");


    Menu *menu = menu_create();
    MenuItem *item0 = menuitem_create();
    menuitem_text(item0, "About");
    menu_add_item(menu, item0);

    
    button_OnClick(button, listener(app, i_OnButton, App));

    
    layout_label(layout1, label, 0, 0);
    layout_button(layout2, button, 0, 0);
    layout_button(layout2, button2, 1, 0);    
    
    layout_hsize(layout, 0, 550);
    layout_vsize(layout, 2, 200);
    layout_margin(layout, 5);
    layout_vmargin(layout, 0, 5);
    layout_vmargin(layout, 1, 5);
    
    layout_layout(layout,layout1,0,0);
    layout_layout(layout,layout2,1,0);    
    layout_textview(layout, text, 0, 2);
    
    panel_layout(panel, layout);
    app->text = text;
    return panel;
}

/*---------------------------------------------------------------------------*/

static void i_OnClose(App *app, Event *e)
{
    osapp_finish();
    unref(app);
    unref(e);
}

/*---------------------------------------------------------------------------*/

static App *i_create(void)
{
    App *app = heap_new0(App);
    Panel *panel = i_panel(app);
    app->window = window_create(ekWINDOW_STD);
    window_panel(app->window, panel);
    window_title(app->window, "CryptText");
    window_origin(app->window, v2df(500, 250));
    window_OnClose(app->window, listener(app, i_OnClose, App));
    window_show(app->window);
    return app;
}

/*---------------------------------------------------------------------------*/

static void i_destroy(App **app)
{
    window_destroy(&(*app)->window);
    heap_delete(app, App);
}

/*---------------------------------------------------------------------------*/

#include <osapp/osmain.h>
osmain(i_create, i_destroy, "", App)
