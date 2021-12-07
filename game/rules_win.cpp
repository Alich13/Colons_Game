#include "../header.h"

/**
 * @brief Construct a new rules win::rules win object
 * 
 */
rules_win::rules_win()
{
    set_title("Rules");				/// Donne un titre a l'application
    resize(400, 300); 							/// Redimensionner la fenêtre
    set_position(Gtk::WIN_POS_CENTER);
    set_resizable(false);	
    card_image = Gdk::Pixbuf::create_from_file("data/Catanes/Cartes/Points.png");
    card_image = card_image->scale_simple((card_image->get_width()) * 0.85, (card_image->get_height()) * 0.8, Gdk::INTERP_BILINEAR);
    Card_Image.set(card_image);

    lbl_.set_label("Colons de Catanes");
    Rules_Grid.attach(lbl_,0,0,1,1);
    Rules_Grid.attach(Card_Image,0,2,1,1);
    mainBox.pack_start(Rules_Grid);
    this->add(mainBox);
    this->show_all_children();
}