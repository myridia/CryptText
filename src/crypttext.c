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
    printf("%s\n",path);
    FILE *file = fopen(path, "w");
    if (!file) 
    {
        perror(path);
        return EXIT_FAILURE;
    }
    if (fputs("Output in file.\n", file) == EOF)
    {
        perror(path);
        e = EXIT_FAILURE;
    }
    if (fclose(file)) 
    {
        perror(path);
        return EXIT_FAILURE;
    }
    
    /*
    if (file != NULL)
    {
      String *s = "h";
      ferror_t error;

      hfile_from_string("zzzzzzz.txt",s,&error);
    }
    */
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
