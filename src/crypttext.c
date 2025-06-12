/* NAppGUI Hello World */

#include <nappgui.h>
#include <stdlib.h>
#include <stdio.h>

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

static void i_OnButton0(App *app, Event *e)
{
    /* printf("%s\n",s);
    */
    const char_t *type[] = { "txt", "ct" };
    const char_t *file = comwin_open_file(app->window, type, 2, NULL);
    Stream *stm = stm_from_file(file,NULL);
    if (stm != NULL) {
    String *s = dbind_read(stm, String);
    textview_printf(app->text,"%s", s);    
    stm_close(&stm);
    }
    unref(e);
}

  /*
    https://devtut.github.io/c/files-and-i-o-streams.html#open-and-write-to-file
   */
static void i_OnButton1(App *app, Event *e)
{
    const char_t *type[] = { "txt" };
    const char_t *path = comwin_save_file(app->window, type, 1, NULL);
    FILE *file = fopen(path, "w");
    String *s = textview_get_text(app->text);

    /* printf("%s\n",s); */
    
    if (!file) 
    {
        perror(path);
        return EXIT_FAILURE;
    }

    
    if (fputs(s, file) == EOF)
    {
        perror(path);
        e = EXIT_FAILURE;
    }
    if (fclose(file)) 
    {
        perror(path);
        return EXIT_FAILURE;
    }
    

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
    Button *button0 = button_push();
    Button *button1 = button_push();
    Button *button2 = button_push();
    Button *button3 = button_push();
    Button *button4 = button_push();
    Button *button5 = button_push();                    
    TextView *text = textview_create();

    
    button_text(button0, "Open");
    button_text(button1, "Save");
    button_text(button2, "Cut");
    button_text(button3, "Copy");
    button_text(button4, "Paste");
    button_text(button5, "Find");                

    textview_editable(text, TRUE); 
    label_text(label, "m1m1");

    
    button_OnClick(button0, listener(app, i_OnButton0, App));
    button_OnClick(button1, listener(app, i_OnButton1, App));    

    
    layout_label(layout1, label, 0, 0);
    layout_button(layout2, button0, 0, 0);
    layout_button(layout2, button1, 1, 0);
    layout_button(layout2, button2, 2, 0);
    layout_button(layout2, button3, 3, 0);
    layout_button(layout2, button4, 4, 0);
    layout_button(layout2, button5, 5, 0);        
    
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
    /*  app->menu = i_menu(app);     */
    app->window = window_create(ekWINDOW_STD);

    window_panel(app->window, panel);
    window_title(app->window, "CryptText");
    window_origin(app->window, v2df(500, 250));
    window_OnClose(app->window, listener(app, i_OnClose, App));


    Menu *menu = menu_create();
    {
    MenuItem *item1 = menuitem_create();
    menuitem_text(item1, "File");

    Menu *submenu = menu_create();
    MenuItem *s_item0 = menuitem_create();
    MenuItem *s_item1 = menuitem_create();
    MenuItem *s_item2 = menuitem_create();
    menuitem_text(s_item0, "New");
    menuitem_text(s_item1, "Open");
    menuitem_text(s_item2, "Exit");
    menu_add_item(submenu, s_item0);
    menu_add_item(submenu, s_item1);
    menu_add_item(submenu, s_item2);
    menuitem_submenu(item1, &submenu);
    menu_add_item(menu, item1);
    }
    {
    MenuItem *item2 = menuitem_create();      
    menuitem_text(item2, "Edit");
    menu_add_item(menu, item2);
    }
    {
    MenuItem *item3 = menuitem_create();      
    menuitem_text(item3, "Help");
    menu_add_item(menu, item3);
    }    
    
    #if defined(__APPLE__)
    Menu *submenu = menu_create();
    MenuItem *item0 = menuitem_create();
    MenuItem *item1 = menuitem_separator();
    MenuItem *item2 = menuitem_create();
    MenuItem *item3 = menuitem_separator();
    MenuItem *item4 = menuitem_create();
    menuitem_text(item0, "About Products");
    menuitem_text(item2, "Settings...");
    menuitem_text(item4, "Quit Products");
    menu_add_item(submenu, item0);
    menu_add_item(submenu, item1);
    menu_add_item(submenu, item2);
    menu_add_item(submenu, item3);
    menu_add_item(submenu, item4);
    MenuItem *xitem = menuitem_create();
    menuitem_text(item, "");
    menuitem_submenu(xitem, &submenu);
    menu_ins_item(menu, 0, xitem);
    #endif

    
    


    osapp_menubar(menu, app->window);

   
    
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
