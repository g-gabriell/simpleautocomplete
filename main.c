#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

typedef struct
{
    GtkWidget * window;
    GtkWidget * grid;
    GtkWidget * textbox;
    GtkTextBuffer * textbuffer;
} AppElements_t;

void textboxPrintWord(GtkWidget * widget, gpointer data)
{
    AppElements_t * app = data;
    /*GtkTextIter iter;
    GtkTextIter wordEnd;
    gchar * text;

    gboolean isWord = FALSE;

    gtk_text_buffer_get_iter_at_mark(app->textbuffer, &iter, gtk_text_buffer_get_insert(app->textbuffer));

    if(gtk_text_iter_inside_word(&iter)) {
        isWord = TRUE;
        wordEnd = iter;
        gtk_text_iter_forward_word_end(&wordEnd);
    }
    else if(gtk_text_iter_ends_word(&iter)) {
        wordEnd = iter;
        isWord = TRUE;
    }

    if(isWord == TRUE) {
        if(!gtk_text_iter_starts_word(&iter)) {
            gtk_text_iter_backward_word_start(&iter);
        }
        text = gtk_text_buffer_get_text(app->textbuffer, &iter, &wordEnd, FALSE);
        printf("%s\n\n", text);
    }*/

    GtkTextIter start;
    GtkTextIter end;
    GtkTextIter lastEnd;
    gchar * text;

    gtk_text_buffer_get_start_iter(app->textbuffer, &start);
    end = start;
    gtk_text_iter_forward_word_end(&end);

    do {
        text = gtk_text_buffer_get_text(app->textbuffer, &start, &end, FALSE);
        lastEnd = end;
        gtk_text_iter_forward_word_ends(&start, 2);
        gtk_text_iter_backward_word_start(&start);
        gtk_text_iter_forward_word_end(&end);
        printf("%s\n", text);
    } while(gtk_text_iter_compare(&end, &lastEnd) != 0);
    printf("\n");
}

void key_event(GtkWidget *widget, gpointer data)
{
    GdkEventKey * event = data;
    __attribute__((unused)) gchar * keyname = gdk_keyval_name (event->keyval);
}

void AppInit(AppElements_t * app)
{
    gtk_init(NULL, NULL);

    // Create window
    app->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(app->window), "Project 1");
    gtk_window_set_default_size(GTK_WINDOW(app->window), 400, 200);
    g_signal_connect(app->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(app->window, "key-release-event", G_CALLBACK(key_event), NULL);

    // Create grid
    app->grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(app->window), app->grid);

    // Create textbox and attach to grid
    app->textbox = gtk_text_view_new();
    app->textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->textbox));
    gtk_widget_set_hexpand(app->textbox, TRUE);
    gtk_widget_set_vexpand(app->textbox, TRUE);
    gtk_grid_attach(GTK_GRID(app->grid), app->textbox, 0, 0, 1, 1);
    g_signal_connect(app->textbuffer, "changed", G_CALLBACK(textboxPrintWord), app);

    // Show app
    gtk_widget_show_all(app->window);
}

int main (int argc, char *argv[])
{
    AppElements_t app;

    AppInit(&app);

    gtk_main();

    return 0;
}
