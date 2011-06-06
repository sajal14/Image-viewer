/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) sajal 2011 <sajal@>
 * 
 * image-viewer is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * image-viewer is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <config.h>

#include <gtk/gtk.h>



/*
 * Standard gettext macros.
 */
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif



#include "callbacks.h"

/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/image_viewer/ui/image_viewer.ui" */
#define UI_FILE "src/image_viewer.ui"
static void
on_open_image (GtkButton* button, gpointer user_data)
{
	GtkWidget *image = GTK_WIDGET (user_data);
	//getting image widget and saving it to toplevel 
	GtkWidget *toplevel1 = gtk_widget_get_toplevel (image);
		//GtkWidget *toplevel2 = gtk_widget_get_toplevel (image2);

	//defining a filter where certain rules can be added such as for image, for cetain patterns etc.
	GtkFileFilter *filter = gtk_file_filter_new ();

	//defining a dialog window(for opening here) 
	// args are : 1.tag line. 2.parent window(here where it is to be opened) 3.action. 4th onwards-> all buttons u want to appear onscreen of dialog box. 
	GtkWidget *dialog = gtk_file_chooser_dialog_new (_("Open image"),
	                                                 GTK_WINDOW (toplevel1),
	                                                 GTK_FILE_CHOOSER_ACTION_OPEN,
	                                                 GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
	                                                 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	                                                 NULL);
	//adding rule for supporting image files in the previously defined filter
	gtk_file_filter_add_pixbuf_formats (filter);

	//now finally adding filter to the dialog. that means the open dialog will look for images whereever you access the folders.
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (dialog),
	                             filter);
	//format for file opening
	if(gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	{
			gchar *filename ;
			filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
			//image set from a file
			gtk_image_set_from_file (GTK_IMAGE (image), filename);
			
		}
	gtk_widget_destroy (dialog);


	
	
}	


GtkWidget*
create_window (void)
{
	GtkWidget *window;
	GtkWidget *button1;
		GtkWidget *button2;
	GtkWidget *image1;
		GtkWidget *image2;
	GtkWidget *hbox;
	GtkWidget *vbox;
	GtkWidget *vbox2;
	GtkWidget *rights;



	window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"my image viewer--devloped by sajal");

	vbox= gtk_vbox_new(FALSE,5);
	vbox2= gtk_vbox_new(FALSE,5);
	hbox=gtk_hbox_new(TRUE,5);
	
	button1 = gtk_button_new_with_label (_("click to open image1"));
		button2 = gtk_button_new_with_label (_("click to open image2"));
	rights= gtk_label_new("This is developed by Sajal");
	//creating widget for image
	image1 = gtk_image_new ();
		image2 = gtk_image_new ();

	gtk_box_pack_start (GTK_BOX (vbox), image1, FALSE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (vbox), button1, FALSE, FALSE, 0);
		
	
	gtk_box_pack_start (GTK_BOX (vbox2), image2, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (vbox2), button2, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (hbox), vbox2, TRUE, TRUE, 0);
	
	//adding box to container
	gtk_container_add (GTK_CONTAINER (window), hbox);

	//calling signals
	
	g_signal_connect (button1, "clicked", G_CALLBACK (on_open_image), image1);
	g_signal_connect (button2, "clicked", G_CALLBACK (on_open_image), image2);
	
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	

	return window;
}


int main (int argc, char *argv[])
{
 	GtkWidget *window;


#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	
	gtk_set_locale ();
	gtk_init (&argc, &argv);

	window = create_window ();
	gtk_widget_show_all (window);

	gtk_main ();
	return 0;
}