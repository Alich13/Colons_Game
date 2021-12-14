#include "header.h"

/**
 * @brief Construct a new rules win::rules win object
 *
 */

thief_win::thief_win(my_window &W) : parent_win(W)
{
    // modify and remove element from parent_class
    set_title("Thief unlocked");
    
    set_position(Gtk::WIN_POS_CENTER);
    this->remove();
    this->set_default_size(600, 400);
    this->set_resizable(false);

    /*
        parent_win.update_resources_table
    */
    px_image = Gdk::Pixbuf::create_from_file("data/vigniettes/7.png");
    px_image = px_image->scale_simple((px_image->get_width()) * 0.5, (px_image->get_height()) * 0.5, Gdk::INTERP_BILINEAR);

    Image.set(px_image);
    
    lbl_.set_label("Colons de Catanes");
    lbl_1.set_label("Chose the cards you want to discard ");
    lbl_2.set_label("");

    main_Grid.set_margin_right(30);
    main_Grid.attach(lbl_, 0, 0, 1, 1);
    main_Grid.attach(Image, 0, 2, 1, 1);
    main_Grid.attach(lbl_1, 0, 3, 1, 1);
    main_Grid.attach(player_info_frame, 0, 4, 1, 1);
    
    mainBox.pack_start(main_Grid);

    this->add(mainBox);
    this->show_all_children();
}

/**
 * @brief filter the input file to only keep the player having 8 or more 
 * 
 * @return vector<Players> filtred
 */
vector<Player> thief_win::filter_8(vector<Player> input_list)
{
    vector<Player> output_list = {} ;

    for (unsigned i ; i < input_list.size();i ++ )
    {
        if (input_list[i].get_resources().size()>=8)
        {
            output_list.push_back(input_list[i]);
        }
    }

    return output_list;
}

/**
 * @brief set the list of plyer having 8 or more ressources
 * and diplay the ressource table for the first player
 * @param N_list call by reference to the list a players from my_window (mainwindow)
 */
void thief_win::set_player_list(vector<Player> &N_list)
{

        /*store here filterd list*/
        this->list_player_with_8_ressources = filter_8(N_list);
        // set resource table and choices
        current_player_itr = list_player_with_8_ressources.begin();
        update_discard_num();
        set_ressources_table();            
        this->show_all_children();

    
}

/**
 * @brief waits for the a signal from submit button to execute all these commands
 *
 * saves previous values
 * passes to the next player with number of cards > 8
 * updates values
 */
void thief_win::submit_choices()
{
    // checks that the user entred the right choices !!
    int discard_num=update_discard_num();
    int discard_choice = spin_argile.get_value()+spin_pierre.get_value()+spin_ble.get_value()+spin_bois.get_value()+spin_mouton.get_value() ;

    if (discard_choice >= discard_num)
    {
        // saves previous results
        // change play ressources values by calling parent win directly

        // pointer toward the player we are modifining
        
        vector<Resources> new_list=update_resources_list();
        Player* player_ptr=parent_win.get_player_by_state(current_player_itr->get_player_STATE_id());
        player_ptr->set_resources(new_list);
        parent_win.update_resources_table();

        if (current_player_itr < next(list_player_with_8_ressources.end(),-1))

        {
            // pass to the next player if exist
            current_player_itr = next(current_player_itr);
            discard_num=update_discard_num();
            update_ressources_table(); // display new values
            this->show_all_children();
             
            
        }
        else
        {
            // saves previous results
            // change play ressources values by calling parent win directly
            // quit
            parent_win.update_resources_table();
            this->close();
            
        }

    }
    else
    {
        Gtk::MessageDialog d(*this, "Please chose " + to_string(discard_num)+ " cards to discard (to eliminate )", true, Gtk::MESSAGE_INFO);
        d.run();
    }
    
    
}


vector<Resources> thief_win::update_resources_list()
{
 vector<Resources> output_list= {};  
 vector<Resources>::iterator new_end;
 vector<Resources> list_to_be_updated= current_player_itr->get_resources();

 for (unsigned i=0;i< (current_player_itr->count_X_ressources(Resources::ble)-spin_ble.get_value());i++) {output_list.push_back(Resources::ble);} ;
 for (unsigned i=0;i< (current_player_itr->count_X_ressources(Resources::bois)-spin_bois.get_value());i++) {output_list.push_back(Resources::bois);} ;
 for (unsigned i=0;i<(current_player_itr->count_X_ressources(Resources::mouton)-spin_mouton.get_value());i++) {output_list.push_back(Resources::mouton);} ;
 for (unsigned i=0;i<(current_player_itr->count_X_ressources(Resources::argile)-spin_argile.get_value());i++) {output_list.push_back(Resources::argile);} ;
 for (unsigned i=0;i<(current_player_itr->count_X_ressources(Resources::pierre)-spin_pierre.get_value());i++) {output_list.push_back(Resources::pierre);} ;

 return  output_list ;


}

void thief_win::update_ressources_table()

{

    player_turn_label.set_markup("<b> Player : " + current_player_itr->get_name() + "</b>");
    score_label.set_markup("<b> Score =" + to_string(current_player_itr->get_score()) + "</b>");
    ble_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::ble)));
    bois_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::bois)));
    mouton_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::mouton)));
    pierre_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::pierre)));
    brick_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::argile)));

    spin_ble.set_range(0,current_player_itr->count_X_ressources(Resources::ble));
    spin_bois.set_range(0,current_player_itr->count_X_ressources(Resources::bois)); 
    spin_mouton.set_range(0,current_player_itr->count_X_ressources(Resources::mouton)); 
    spin_pierre.set_range(0,current_player_itr->count_X_ressources(Resources::pierre));
    spin_argile.set_range(0,current_player_itr->count_X_ressources(Resources::argile)); 


}
/**
 * @brief update label values and !!!! return the actual value of cards to discard 
 * 
 * @return int 
 */
int  thief_win::update_discard_num()
{

    /* diplay number of cards to discard */
    if (current_player_itr->get_resources().size()%2==0 )
    {
        string carte_to_discard =to_string( ( current_player_itr->get_resources().size() )/2 );
        lbl_2.set_label("You must discard (eliminate) " + carte_to_discard);
        return current_player_itr->get_resources().size() /2;
    }
    else 
    {
        string carte_to_discard =to_string( ( current_player_itr->get_resources().size() - 1 )/2 );
        lbl_2.set_label("You must discard (eliminate) " + carte_to_discard);
        return (current_player_itr->get_resources().size()-1) /2;
    }

}

void thief_win::set_ressources_table()

{
    

    button_submit.set_label("Do");
    button_submit.signal_clicked().connect(sigc::mem_fun(*this, &thief_win::submit_choices));
    

    player_turn_label.set_markup("<b> Player : " + current_player_itr->get_name() + "</b>");
    score_label.set_markup("<b> Score =" + to_string(current_player_itr->get_score()) + "</b>");

    ble_title.set_markup("Blé");
    ble_image = Gdk::Pixbuf::create_from_file("data/ressources/Ble.png");
    ble_image = ble_image->scale_simple((ble_image->get_height()) * 0.10, (ble_image->get_width()) * 0.20, Gdk::INTERP_BILINEAR);
    ble_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::ble)));
    Ble_Image.set(ble_image);
    spin_ble.set_range(0,current_player_itr->count_X_ressources(Resources::ble)); 
    spin_ble.set_value(0);
    spin_ble.set_increments(1,1);


    bois_title.set_markup("Bois");
    bois_image = Gdk::Pixbuf::create_from_file("data/ressources/Bois.png");
    bois_image = bois_image->scale_simple((bois_image->get_height()) * 0.10, (bois_image->get_width()) * 0.20, Gdk::INTERP_BILINEAR);
    bois_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::bois)));
    Bois_Image.set(bois_image);
    spin_bois.set_range(0,current_player_itr->count_X_ressources(Resources::bois)); 
    spin_bois.set_value(0);
    spin_bois.set_increments(1,1);

    mouton_title.set_markup("Moutons");
    mouton_image = Gdk::Pixbuf::create_from_file("data/ressources/Mouton.png");
    mouton_image = mouton_image->scale_simple((mouton_image->get_height()) * 0.10, (mouton_image->get_width()) * 0.20, Gdk::INTERP_BILINEAR);
    mouton_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::mouton)));
    Mouton_Image.set(mouton_image);
    spin_mouton.set_range(0,current_player_itr->count_X_ressources(Resources::mouton)); 
    spin_mouton.set_value(0);
    spin_mouton.set_increments(1,1);

    pierre_title.set_markup("Pierre");
    pierre_image = Gdk::Pixbuf::create_from_file("data/ressources/Pierre.png");
    pierre_image = pierre_image->scale_simple((pierre_image->get_height()) * 0.10, (pierre_image->get_width()) * 0.20, Gdk::INTERP_BILINEAR);
    pierre_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::pierre)));
    Pierre_Image.set(pierre_image);
    spin_pierre.set_range(0,current_player_itr->count_X_ressources(Resources::pierre)); 
    spin_pierre.set_value(0);
    spin_pierre.set_increments(1,1);

    brick_title.set_markup("Briques");
    argile_image = Gdk::Pixbuf::create_from_file("data/ressources/Brique.png");
    argile_image = argile_image->scale_simple((argile_image->get_height()) * 0.10, (argile_image->get_width()) * 0.20, Gdk::INTERP_BILINEAR);
    brick_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::argile)));
    Argile_Image.set(argile_image);
    spin_argile.set_range(0,current_player_itr->count_X_ressources(Resources::argile)); 
    spin_argile.set_value(0);
    spin_argile.set_increments(1,1);

    //---------------Attach element -------------------------//
    infoGrid.set_row_spacing(30);
    infoGrid.set_column_spacing(20);
    infoGrid.set_margin_left(150);
    infoGrid.set_margin_top(20);
    infoGrid.attach(player_turn_label, 0, 0, 1, 1);
    infoGrid.attach(score_label, 0, 1, 1, 1);

    ressourcesGrid.set_margin_left(20);
    ressourcesGrid.set_column_spacing(20);
    ressourcesGrid.set_row_spacing(20);

    ressourcesGrid.attach(ble_title, 0, 2, 1, 1);
    ressourcesGrid.attach(Ble_Image, 0, 3, 1, 1);
    ressourcesGrid.attach(ble_count_label, 0, 4, 1, 1);
    ressourcesGrid.attach(spin_ble, 0, 5, 1, 1);

    ressourcesGrid.attach(bois_title, 1, 2, 1, 1);
    ressourcesGrid.attach(Bois_Image, 1, 3, 1, 1);
    ressourcesGrid.attach(bois_count_label, 1, 4, 1, 1);
    ressourcesGrid.attach(spin_bois, 1, 5, 1, 1);

    ressourcesGrid.attach(mouton_title, 2, 2, 1, 1);
    ressourcesGrid.attach(Mouton_Image, 2, 3, 1, 1);
    ressourcesGrid.attach(mouton_count_label, 2, 4, 1, 1);
    ressourcesGrid.attach(spin_mouton, 2, 5, 1, 1);

    ressourcesGrid.attach(pierre_title, 3, 2, 1, 1);
    ressourcesGrid.attach(Pierre_Image, 3, 3, 1, 1);
    ressourcesGrid.attach(pierre_count_label, 3, 4, 1, 1);
    ressourcesGrid.attach(spin_pierre, 3, 5, 1, 1);

    ressourcesGrid.attach(brick_title, 4, 2, 1, 1);
    ressourcesGrid.attach(Argile_Image, 4, 3, 1, 1);
    ressourcesGrid.attach(brick_count_label, 4, 4, 1, 1);
    ressourcesGrid.attach(spin_argile, 4, 5, 1, 1);

    player_info_frame.set_label("Player info");
    player_info_frame.set_margin_left(50);
    ressouces_frame.set_label("Ressources");
    player_info_box.set_spacing(20);
    player_info_box.set_margin_bottom(20);
    player_info_box.set_margin_left(20);
    player_info_box.set_margin_bottom(20);
    player_info_box.set_margin_right(20);
    player_info_box.pack_start(infoGrid);
    ressouces_frame.add(ressourcesGrid);
    player_info_box.pack_start(ressouces_frame);
    player_info_box.pack_start(button_submit);
    player_info_box.pack_start(lbl_2);
    
    player_info_frame.add(player_info_box);
}
