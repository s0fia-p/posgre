#include <gtk/gtk.h>
#include <postgresql/libpq-fe.h>

GtkWidget *entry1, *entry2;
GtkWidget *text1;
char a[4][100]={"Tolstoy", "Tolstoy", "Pushkin", "Bulgakov"},
     b[4][100]={"War and Peace", "Anna Karenina", "Ruslan and Ludmila", "THe Master and Margarita"};
int c[4]={10, 2, 0, 7};



void ok1 (GtkWidget *widget)
{
  char op[100], tmp[100];
  int k=0, i, j, n;
  strcpy (tmp, gtk_entry_get_text((GtkEntry *)entry1));
  sprintf (op, "His book(s):\n");
  for (i=0; i<4; i++){
    n=0;
    for (j=0; j<6; j++) {if (tmp[j]==a[i][j])n++;}
    if (n==6) {
      k++;
      sprintf (op, "%s%s%s%d%s", op, b[i], " (", c[i], ")\n");
    }
  }
  if (k==0) sprintf (op, "There is no such author.");
  gtk_label_set_label((GtkLabel *) text1, op);
}

void ok2 (GtkWidget *widget)
{
  char op[100], tmp[100];
  int k=0, i, j, n;
  strcpy (tmp, gtk_entry_get_text((GtkEntry *)entry1));
  sprintf (op, "The author of this book is \n");
  for (i=0; i<4; i++){
    n=0;
    for (j=0; j<6; j++) {if (tmp[j]==b[i][j])n++;}
    if (n==6) {
      k++;
      sprintf (op, "%s%s%s%d%s", op, a[i], "\nThere is ", c[i], " book(s) in our library");
      break;
    }
  }
  if (k==0) sprintf (op, "There is no such book.");
  gtk_label_set_label((GtkLabel *) text1, op);

}
void bo (GtkWidget *widget)
{
  char op[100], tmp[100];
  int k=0, i, j, n;
  strcpy (tmp, gtk_entry_get_text((GtkEntry *)entry1));
  for (i=0; i<4; i++){
    n=0;
    for (j=0; j<6; j++) {if (tmp[j]==b[i][j])n++;}
    if (n==6) {
      k++;
      if (c[i]>0) {
        c[i]--;
        sprintf (op, "Ok");
      }else {sprintf (op, "%s", "Sorry,\nthere is no such book at the moment.");}
      break;
    }
  }
  if (k==0) {sprintf (op, "Sorry, you cannot book this.");}
  gtk_label_set_label((GtkLabel *) text1, op);
}


int main(int argc, char *argv[])
{
  GtkWidget *window, *frame;
  GtkWidget *lbooking, *booking;
  GtkWidget *label1, *label2;
  GtkWidget *okb1, *lokb1, *okb2, *lokb2;
  GtkWidget *qb, *lqb;

  PangoFontDescription *myfont = pango_font_description_from_string("Arial 26");
  gtk_init(&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "PostgreSQL");
  gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);

  label1 = gtk_label_new("Author OR Book");
  gtk_widget_modify_font (label1, myfont);
  gtk_fixed_put(GTK_FIXED(frame), label1, 50, 40);

  entry1 = gtk_entry_new();
  gtk_widget_modify_font(entry1, myfont);
  gtk_entry_set_width_chars((GtkEntry *)entry1, 26);
  gtk_fixed_put(GTK_FIXED(frame), entry1, 50, 80);



  lokb1 = gtk_label_new("Author");
  gtk_widget_modify_font (lokb1, myfont);
  okb1 = gtk_button_new ();
  gtk_container_add(GTK_CONTAINER(okb1), lokb1);
  gtk_fixed_put(GTK_FIXED(frame), okb1, 200, 180);

  lokb2 = gtk_label_new("Book");
  gtk_widget_modify_font (lokb2, myfont);
  okb2 = gtk_button_new ();
  gtk_container_add(GTK_CONTAINER(okb2), lokb2);
  gtk_fixed_put(GTK_FIXED(frame), okb2, 400, 180);

  lbooking = gtk_label_new("Booking");
  gtk_widget_modify_font (lbooking, myfont);
  booking = gtk_button_new ();
  gtk_container_add(GTK_CONTAINER(booking), lbooking);
  gtk_fixed_put(GTK_FIXED(frame), booking, 300, 380);

  lqb = gtk_label_new("Quit");
  gtk_widget_modify_font (lqb, myfont);
  qb = gtk_button_new ();
  gtk_container_add(GTK_CONTAINER(qb), lqb);
  gtk_fixed_put(GTK_FIXED(frame), qb, 450, 380);

  text1 = gtk_label_new("");
  gtk_widget_modify_font (text1, myfont);
  gtk_fixed_put(GTK_FIXED(frame), text1, 50, 240);


  gtk_widget_show_all(window);

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(okb1, "clicked", G_CALLBACK(ok1), NULL);
  g_signal_connect(okb2, "clicked", G_CALLBACK(ok2), NULL);
  g_signal_connect(booking, "clicked", G_CALLBACK(bo), NULL);
  g_signal_connect(qb, "clicked", G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();
  return 0;
}
