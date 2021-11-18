#include "header.h"
#include <cairomm/context.h>
#include <iostream>
#define SCALE 1.25
using namespace std;

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& My window   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/

/**
 * @brief Construct a new my window::my window object
 *
 */
my_window::my_window()
{

    /*----------setup window-------------------------------*/
    set_title("Colons Game !");
    set_position(Gtk::WIN_POS_CENTER);
    set_default_size(1405, 905); //+5 size of all the window for the border
    // fullscreen();	
    set_border_width(5);
    /*--------------setup window----------------*/

    set_my_menu(); // method to set up the menu
    set_side_box();

    /*---------board box---------------*/
    board_Frame.set_label("Game Board");
    board_Frame.add(dessin);
    board_box.set_size_request(1000, 900); // (width,hight) (1000,900)
    board_box.add(board_Frame);
    /*---------board box---------------*/

    /*---------mainGrid-------------------------*/
    mainGrid.set_row_spacing(10);
    mainGrid.set_column_spacing(10);
    mainGrid.attach(buttons_box, 0, 1, 1, 1);
    mainGrid.attach(board_box, 1, 1, 1, 1);
    mainLayout.add(mainGrid);
    add(mainLayout);     // ajoute la grid à la fenetre
    show_all_children(); // afficher tous les grid inclus dans la fènete
    /*---------mainGrid-------------------------*/
}

//--------------------------------------------------------------//

void my_window::button_add_house()
{
    // set all other bottons to false
    dessin.set_add_route_pressed(false);

    Gtk::MessageDialog d(*this, "Choose your house position ", true, Gtk::MESSAGE_INFO);
    d.run();
    dessin.set_add_house_pressed(true);
}

//--------------------------------------------------------------//

void my_window::button_add_route()
{
    // alerte widjet
    // set all other bottons to false
    dessin.set_add_house_pressed(false);

    Gtk::MessageDialog d(*this, "Choose a route to build ", true, Gtk::MESSAGE_INFO);
    d.run();
    dessin.set_add_route_pressed(true);
}

/**
 * @brief passes to the next turn ie changes player
 *
 */
void my_window::next_turn()
{
    /*----------------reset dice parameters-----------------------------*/
    my_dice.set_dice_state(true);
    this->dice_value = 0;
    Dice_output_label.set_markup(" Throw Dice ? ? ?");
    Dice_Image.clear();
    /*-----------------------------------------------------*/

    if (current_player_itr < next(player_list.end(), -1))
    {
        current_player_itr = next(current_player_itr);
        cout << "player " << current_player_itr->get_player_INT_id() << "'s turn" << endl;
        player_turn_label.set_markup("<b>player :" + current_player_itr->get_name() + "</b>");

        //-----current_player =*current_player_itr;
        dessin.setActivePlayer(&*current_player_itr); //*current_player_itr gives us the player and
                                                      //  &*current_player_itr gives us the address
        // put dice in active state
    }
    else
    {
        current_player_itr = player_list.begin();
        cout << "player " << current_player_itr->get_player_INT_id() << "'s turn" << endl;
        player_turn_label.set_markup("<b>player :" + current_player_itr->get_name() + "</b>");
        dessin.setActivePlayer(&*current_player_itr);
        // put dice in active state
    }
}

void my_window::diplay_dice_visual_effect(int dice_num)
{
    cout << my_dice.randomize_dice() << endl;
    dice_image = Gdk::Pixbuf::create_from_file("data/vigniettes/" + to_string(dice_num) + ".png");
    dice_image = dice_image->scale_simple((dice_image->get_height()) * 0.5, (dice_image->get_width()) * 0.5, Gdk::INTERP_BILINEAR);
    Dice_Image.set(dice_image);
    unsigned int seconds = 2;
    sleep(seconds); // sleeps for  second
    show_all_children();
    
}

void my_window::play_dice()
{
    if (my_dice.get_dice_state() == true)
    {
        //----------------------------------visual effect-----------------------------//
        // can do it with pixful


        this->dice_value = my_dice.randomize_dice();
        my_dice.set_dice_state(false);
        Dice_output_label.set_markup("returned value = " + to_string(dice_value));
        dice_image = Gdk::Pixbuf::create_from_file("data/vigniettes/" + to_string(dice_value) + ".png");
        dice_image = dice_image->scale_simple((dice_image->get_height()) * 0.5, (dice_image->get_width()) * 0.5, Gdk::INTERP_BILINEAR);
        Dice_Image.set(dice_image);
    }
    else
    {
        Gtk::MessageDialog d(*this, "Can not play more than one time in a turn !!  ", true, Gtk::MESSAGE_ERROR);
        d.run();
    }
}

//--------------------------------------------------------------//

void my_window::set_my_menu()
{
    mainLayout.pack_start(menuBar, Gtk::PACK_SHRINK);
    // Create the menu item files
    menuFiles.set_label("Files");
    menuBar.append(menuFiles);
    // Create a sub menu in files
    menuFiles.set_submenu(subMenuFiles);
    open.set_label("OPEN");
    subMenuFiles.append(open);
    close.set_label("CLOSE");
    subMenuFiles.append(close);
    subMenuFiles.append(hline); // Add a separator
    quit.set_label("QUIT");
    subMenuFiles.append(quit);
    // Create the menu item Edit
    menuEdit.set_label("Edit");
    menuBar.append(menuEdit);
    // ::: Create the event for MenuItem :::
    quit.signal_activate().connect(sigc::ptr_fun(&Gtk::Main::quit));
}

void my_window::set_side_box()
{

    /*---------- info frame---------------*/
    // dessin.setActivePlayer(&*current_player_itr);
    player_turn_label.set_markup("<b> Player : " + current_player_itr->get_name() + "</b>");
    Ressources_label.set_markup("<b> --Ressources-- </b>");
    ble_count_label.set_markup("15");
    
    ble_image = Gdk::Pixbuf::create_from_file("data/ressources/Ble.png");
    ble_image = ble_image->scale_simple((ble_image->get_height()) * 0.10, (ble_image->get_width()) * 0.20, Gdk::INTERP_BILINEAR);
    Ble_Image.set(ble_image);

    bois_image = Gdk::Pixbuf::create_from_file("data/ressources/Bois.png");
    bois_image = bois_image->scale_simple((bois_image->get_height()) * 0.10, (bois_image->get_width()) * 0.20, Gdk::INTERP_BILINEAR);
    Bois_Image.set(bois_image);

    mouton_image = Gdk::Pixbuf::create_from_file("data/ressources/Mouton.png");
    mouton_image = mouton_image->scale_simple((mouton_image->get_height()) * 0.10, (mouton_image->get_width()) * 0.20, Gdk::INTERP_BILINEAR);
    Mouton_Image.set(mouton_image);
    
    infoGrid.set_row_spacing(10);
    infoGrid.set_column_spacing(5);
    infoGrid.attach(player_turn_label, 0, 0, 1, 1);
    infoGrid.attach(Ressources_label, 0, 1, 1, 1);
    infoGrid.attach(Ble_Image,0, 2, 1, 1);
    infoGrid.attach(ble_count_label,0, 3, 1, 1);
    infoGrid.attach(Bois_Image,1, 2, 1, 1);
    
    player_info_frame.set_label("Player info");
    player_info_frame.add(infoGrid);

    /*---------buttons box--------------*/
    button_house.add_label("Build a House");
    button_house.signal_clicked().connect(sigc::mem_fun(*this, &my_window::button_add_house));
    button_route.add_label("Build Route");
    button_route.signal_clicked().connect(sigc::mem_fun(*this, &my_window::button_add_route));
    button_next_turn.add_label("Next Turn");
    button_next_turn.signal_clicked().connect(sigc::mem_fun(*this, &my_window::next_turn));
    // | //
    // v //
    buttonsGrid.set_margin_left(20);
    buttonsGrid.set_row_spacing(10);
    buttonsGrid.set_column_spacing(10);
    buttonsGrid.attach(button_house, 0, 0, 1, 1);
    buttonsGrid.attach(button_route, 0, 1, 1, 1);
    buttonsGrid.attach(button_next_turn, 0, 2, 1, 1);
    // | //
    // v //
    action_buttons_frame.set_label("Action Buttons");
    action_buttons_frame.add(buttonsGrid);
    /*---------- Dice output frame---------------*/

    Dice_output_label.set_markup(" Throw Dice ? ? ?");
    button_play_dice.set_label("Play Dice");
    button_play_dice.signal_clicked().connect(sigc::mem_fun(*this, &my_window::play_dice));

    DiceGrid.set_margin_left(20);
    DiceGrid.set_row_spacing(10);
    DiceGrid.set_column_spacing(15);

    DiceGrid.attach(button_play_dice, 0, 0, 1, 1);
    DiceGrid.attach(Dice_output_label, 1, 0, 1, 1);
    DiceGrid.attach(Dice_Image, 2, 0, 1, 1);

    // Dice_grid.attach(button_play_dice,1,1,1,1);
    dice_output_frame.add(DiceGrid);
    dice_output_frame.set_label("Dice");
    /*--------------------------------------------*/
    // | //
    // v //
    buttons_box.set_spacing(10);
    buttons_box.set_size_request(600, 900);
    buttons_box.pack_start(player_info_frame, 0, 0);
    buttons_box.pack_start(action_buttons_frame, 0, 0);
    buttons_box.pack_start(dice_output_frame, 0, 0);
    /*---------buttons box--------------*/
}