#ifndef STDLIB_STDIO
#define STDLIB_STDIO

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>

#endif
#include <err.h>

#include "Pretraitement/pretraitement.h"
#include "Pretraitement/pixel_operations.h"
#include "Chargement/load.h"
#include "Extraction/extraction_operations.h"
#include "Extraction/extract_text_bloc.h"

static GtkWidget *text_view;

void OnDestroy(/*GtkWidget *pWidget, gpointer pData*/);
void saisie(/*GtkButton *button*/);
void saisir_fichier(/*GtkWidget *bouton,*/ GtkWidget *file_selection);
void ouvrir_img(GtkButton *button, GtkImage *pImage);
void save();
void retablir_img(GtkButton *button, GtkImage *pImage);
int interface (int argc, char**argv, SDL_Surface *img);


void wait_for_keypressed(void)
{
	SDL_Event event;
	for (;;)
	{
		SDL_WaitEvent( &event );
		switch (event.type)
		{
			case SDL_KEYDOWN : return;
			default: break;
		}
	}
}

SDL_Surface* display_image(SDL_Surface *img)
{
	SDL_Surface          *screen;
  // Set the window to the same size as the image
	screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
	if ( screen == NULL )
	{
    // error management
		errx(1, "Couldn't set %dx%d video mode: %s\n",
			img->w, img->h, SDL_GetError());
	}
  /* Blit onto the screen surface */
  /*if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());*/

  // Update the screen
	SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  // wait for a key
	wait_for_keypressed();

  // return the screen for further uses
	return screen;
}

void greyscale(char **path)
{
	const char* output_g = "./Result/grey.bmp";

	SDL_Surface *img;

	if(isFileExist(path))
		img = loadImage(path);

	Greyscale(img);

	SDL_SaveBMP(img,  output_g);

	SDL_Surface(img);

	*path = output_g;

}

void binary(const char **path)
{
	const char* output_b = "./Result/binary.bmp";

	SDL_Surface *img;

	if(isFileExist(*path))
		img = loadImage(*path);

	whiteBlack(img);

	SDL_SaveBMP(img, output_b);
	SDL_SaveBMP(img,output);

	SDL_FreeSurface(img);

	*path = output_b;
}

void extract_data_from_image(char **path)
{
	const char* output_detected = "./Result/detection.bmp";

	SDL_Surface *img;

	int nbblocs;
	TextBlocList *tb;


	if(isFileExist(*path))
		img = loadImage(*path);

  /*Extract Bloc*/

  /*####Temporary####*/
	tb = malloc(sizeof(TextBlocList));

	tb->next = NULL;
	tb->x = 0;
	tb->y = 0;
	tb->w = img->w;
	tb->h = img->h;

	TextBlocList *tmp = tb;
	nbblocs = 0;
	for(; tmp; tmp = tmp->next)
		nbblocs++;

  /*Extract Lines and Character*/

	for (int i = 0; i < nbblocs; i++) 
		SegmentLines(img,tb);

	if(!img)
	SDL_SaveBMP(img,output_detected);

  SDL_FreeSurface(img)

  *path = output_b;
}

int main (int argc, char* argv[])
{
	SDL_Surface *img = NULL;

	if(argc == 2 && isFileExist(argv[1]))
	{
		img = loadImage(argv[1]);
		SDL_SaveBMP(img,"./Result/backup.bmp");
		remove("./Result/detection.bmp");
		remove("./Result/binary.bmp");
		remove("./Result/grey");
		remove("./Result/output.bmp");
		SDL_FreeSurface(img);
	}
	else
		return EXIT_FAILURE;

	if( SDL_Init(SDL_INIT_VIDEO)==-1 ) 
		return EXIT_FAILURE;

	interface(argc,argv,argv[1]);

	return EXIT_SUCCESS;
}

int interface(int argc, char **argv, char * path)
{
	/* Initialisation de GTK+ */
	GtkWidget *pWindow, 
	*pHbox,
		  *pVbox, /*Contient 2 frames*/
	*pVbox1, 
	*pVbox2,
	*pVbox3,
	*pButton[10],
	*pVbox1Frame,
	*pVbox2Frame,
	*pVbox3Frame,
	*pBtnTxt,
	*scrollbar,
	*scrollbar2;
	GtkWidget  *pImage;
	//	SDL_Surface *display;
	gtk_init(&argc, &argv);

	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL); //Creation
	gtk_window_set_title(GTK_WINDOW(pWindow), "Mental Twist Algorithm");
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 1000, 1000);
	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER); //Position
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	pHbox = gtk_hbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(pWindow), pHbox);

	/* VBox1 à gauche */
	pVbox = gtk_vbox_new(TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pHbox), pVbox, TRUE, TRUE, 0);



	/* 1ere frame */ /*contient l'image*/
	pVbox1Frame = gtk_frame_new("Texte Original"); 
	gtk_box_pack_start(GTK_BOX(pVbox), pVbox1Frame, TRUE, TRUE, 0); /*Inclus dans VBox1*/

	pVbox1 = gtk_vbox_new(FALSE, 5); /*Inclus dans frame*/
	gtk_container_add(GTK_CONTAINER(pVbox1Frame), pVbox1);

	scrollbar = gtk_scrolled_window_new(NULL, NULL);
	gtk_box_pack_start(GTK_BOX(pVbox1), scrollbar, TRUE, TRUE, 5);

	pImage = NULL;
	if(argc == 2)
	{
		GError *err =NULL;
		GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(argv[1],&err);
		pImage=gtk_image_new_from_pixbuf(pixbuf);

	}

	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollbar), pImage);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);	

	pButton[0] = gtk_button_new_with_label("Charger l'image"); /*Button*/
	gtk_box_pack_start(GTK_BOX(pVbox1), pButton[0], FALSE, FALSE, 0);
	pButton[9] = gtk_button_new_with_label("Rétablir l'image originale");
	gtk_box_pack_start(GTK_BOX(pVbox1), pButton[9], FALSE, FALSE, 0);


	g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(ouvrir_img), GTK_IMAGE(pImage));
	g_signal_connect(G_OBJECT(pButton[9]), "clicked", G_CALLBACK(retablir_img), GTK_IMAGE(pImage));


	/* 2ème frame */ /*contient zone de texte*/
	pVbox2Frame = gtk_frame_new("Résultat.txt");
	gtk_box_pack_start(GTK_BOX(pVbox), pVbox2Frame, TRUE, TRUE, 0); /*Inclus dans VBox1*/

	pVbox2 = gtk_vbox_new(FALSE, 5); /*Inclus dans 2eme frame*/
	gtk_container_add(GTK_CONTAINER(pVbox2Frame), pVbox2);

	scrollbar2 = gtk_scrolled_window_new(NULL, NULL);
	gtk_box_pack_start(GTK_BOX(pVbox2), scrollbar2, TRUE, TRUE, 5);

	text_view = gtk_text_view_new();
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollbar2), text_view); /*fenetre de texte */

	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar2), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

	pBtnTxt = gtk_button_new_with_label("Sélectionnez fichier");
	gtk_box_pack_start(GTK_BOX(pVbox2), pBtnTxt, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(pBtnTxt), "clicked", G_CALLBACK(saisie), NULL);



	/* 3ème frame à droite */ /*contient menu*/
	pVbox3Frame = gtk_frame_new("Menu"); /*Inclus dans HBox*/
	gtk_box_pack_start(GTK_BOX(pHbox), pVbox3Frame, FALSE, FALSE, 0);

	pVbox3 = gtk_vbox_new(TRUE, 0); /*Inclus dans 3ème frame*/
	gtk_container_add(GTK_CONTAINER(pVbox3Frame), pVbox3);

	pButton[1] = gtk_button_new_with_label("Lancer la détection");
	pButton[7] = gtk_button_new_with_label("Sauvegarde");
	pButton[6] = gtk_button_new_with_label("Reconnaissance");
	pButton[8] = gtk_button_new_with_label("Quitter");
	pButton[2] = gtk_button_new_with_label("Niveau de gris");
	pButton[3] = gtk_button_new_with_label("Noir et blanc");
	pButton[4] = gtk_button_new_with_label("Flou");
	pButton[5] = gtk_button_new_with_label("Rotation");

	gtk_box_pack_start(GTK_BOX(pVbox3), pButton[2], TRUE, TRUE, 0); /*Dans Vbox3*/
	gtk_box_pack_start(GTK_BOX(pVbox3), pButton[3], TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pVbox3), pButton[4], TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pVbox3), pButton[5], TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pVbox3), pButton[1], TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pVbox3), pButton[6], TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pVbox3), pButton[7], TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pVbox3), pButton[8], TRUE, TRUE, 0);



	g_signal_connect(G_OBJECT(pButton[2]), "clicked", G_CALLBACK(greyscale), &path);
	g_signal_connect(G_OBJECT(pButton[3]), "clicked", G_CALLBACK(binary), &path);
	//g_signal_connect(G_OBJECT(pButton[4]), "clicked", G_CALLBACK(flou), &path); 
	//g_signal_connect(G_OBJECT(pButton[5]), "clicked", G_CALLBACK(rotation), &path);  
	g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(extract_data_from_image), &path);  
	g_signal_connect(G_OBJECT(pButton[8]), "clicked", G_CALLBACK(gtk_main_quit), NULL); /*Quitte*/
	g_signal_connect(G_OBJECT(pButton[7]), "clicked", G_CALLBACK(save), NULL);

	gtk_widget_show_all(pWindow); //Affichage de pWindow et de ce qu'il contient
	gtk_main();


	//gtk_widget_destroy(pWindow); //Detruction
	return 0;
}


void OnDestroy(/*GtkWidget *pWidget, gpointer pData*/)
{
	gtk_main_quit(); //Arret de la boucle
}

void saisie(/*GtkButton *button*/)  /*Recherche du fichier*/
{
	GtkWidget *selection;
	selection = gtk_file_selection_new("selectionnez un fichier");
	gtk_widget_show(selection);
	g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(saisir_fichier), selection);
	g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}

void saisir_fichier(/*GtkWidget *bouton,*/ GtkWidget *file_selection) /*ouverture du fichier*/
{
	GtkTextBuffer *buffer;
	GtkTextIter start;
	GtkTextIter end;
	FILE *fichier;
	const gchar *chemin;
	gchar lecture[1024];

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

	chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION(file_selection));
	fichier = fopen(chemin, "r");

	if(fichier == NULL)
	{
		GtkWidget *dialog;

		dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "impossible d'ouvrir le fichier : \n%s", chemin);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		gtk_widget_destroy(file_selection);
		return;
	}

	gtk_widget_destroy(file_selection);

	gtk_text_buffer_get_start_iter(buffer, &start);
	gtk_text_buffer_get_end_iter(buffer, &end);
	gtk_text_buffer_delete(buffer, &start, &end);

	while(fgets(lecture, 1024, fichier))
	{
		gtk_text_buffer_get_end_iter(buffer, &end);
		gtk_text_buffer_insert(buffer, &end, lecture, -1);
	}

	fclose(fichier);
}

void ouvrir_img(GtkButton *button,  GtkImage *pImage) //changement d'image
{
	if(button){
		GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("./Result/output.bmp",NULL); //chargement du resultat des traitement image
		gtk_image_set_from_pixbuf((GtkImage*) pImage, pixbuf);
	}
}

void save() //sauvegarde du fichier .txt
{
	GtkTextBuffer *buffer1;
	GtkTextIter start;
	GtkTextIter end;
	gchar *text;
	//gboolean result;
	//GError *err;
	FILE *file;


	gtk_widget_set_sensitive (text_view, FALSE);
	buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
	gtk_text_buffer_get_start_iter (buffer1, &start);
	gtk_text_buffer_get_end_iter (buffer1, &end);
	text = gtk_text_buffer_get_text (buffer1, &start, &end, FALSE);
	gtk_text_buffer_set_modified (buffer1, FALSE);
	gtk_widget_set_sensitive (text_view, TRUE);

	file = fopen("./Result/output.bmp", "w+");

	if(file)
	{
		printf("%s\n",text);
		fprintf(file, "%s",text); 
	}
	fclose(file);
	//result = g_file_set_contents ("./output.txt", text, -1, &err);

	/*if (result == FALSE)
	  {
	//error saving file, show message to user 
	error_message (err->message);
	g_error_free (err);
	} */       

	g_free (text); 


}

void retablir_img(GtkButton *button, GtkImage *pImage)
{
	if(button){
		GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("./Result/backup.bmp",NULL); //chargement du resultat des traitement image
		gtk_image_set_from_pixbuf((GtkImage*) pImage, pixbuf);
	}

}


