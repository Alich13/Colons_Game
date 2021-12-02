#include "../header.h"
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
my_window::my_window() : dessin(*this)
{
    //-----------------------------load css-----------------------------
    Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();
    cssProvider->load_from_path("style.css");
    Glib::RefPtr<Gtk::StyleContext> styleContext = Gtk::StyleContext::create();
    // get default screen
    Glib::RefPtr<Gdk::Screen> screen = Gdk::Screen::get_default();
    // add provider for screen in all application
    styleContext->add_provider_for_screen(screen, cssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    Glib::RefPtr<Gtk::StyleContext> context = this->get_style_context();
    context->add_class("my_window");

    /*----------setup window-------------------------------*/
    set_title("Colons Game !");
    set_position(Gtk::WIN_POS_CENTER);
    set_default_size(1405, 905); //+5 size of all the window for the border
    // fullscreen();
    set_border_width(5);

    /*-------------set init phase----------------*/
    dessin.route_map.set_init_phase_on();

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

void my_window::button_add_house()
{
    // first phase
    if (first_turns == true)
    {
        if (
            ((current_player_itr->get_score() == 0) && (inversed == false)) ||
            ((current_player_itr->get_score() == 1) && (inversed == true)) ||
            ((current_player_itr->get_score() == 0) && (inversed == true)) // When iterator is on last element
        )
        {
            // set all other bottons to false
            dessin.set_add_route_pressed(false);
            Gtk::MessageDialog d(*this, "Choose your house position ", true, Gtk::MESSAGE_INFO);
            d.run();
            dessin.set_add_house_pressed(true);
        }
        else
        {
            Gtk::MessageDialog d(*this, "Can't place more than one house ", true, Gtk::MESSAGE_ERROR);
            d.run();
        }
    }
    // second phase
    if (first_turns == false)
    {
        // set all other bottons to false
        dessin.set_add_route_pressed(false);
        Gtk::MessageDialog d(*this, "Choose your house position ", true, Gtk::MESSAGE_INFO);
        d.run();
        dessin.set_add_house_pressed(true);
    }
}

void my_window::button_add_route()
{
    if (first_turns == true)
    {
        cout << "route number" <<current_player_itr->get_number_of_routes() << endl ;
        if (
            ((current_player_itr->get_number_of_routes() == 0) && (inversed == false)) ||
            ((current_player_itr->get_number_of_routes() == 1) && (inversed == true)) ||
            ((current_player_itr->get_number_of_routes() == 0) && (inversed == true))
        )
        {
            // alerte widjet
            // set all other bottons to false
            dessin.set_add_house_pressed(false);
            Gtk::MessageDialog d(*this, "Choose a route to build ", true, Gtk::MESSAGE_INFO);
            d.run();
            dessin.set_add_route_pressed(true);
        }
        else
        {
            Gtk::MessageDialog d(*this, "Can't place more than one Route ", true, Gtk::MESSAGE_ERROR);
            d.run();
        }
    }
    // second phase
    if (first_turns == false)
    {
        // alerte widjet
        // set all other bottons to false
        dessin.set_add_house_pressed(false);

        Gtk::MessageDialog d(*this, "Choose a route to build ", true, Gtk::MESSAGE_INFO);
        d.run();
        dessin.set_add_route_pressed(true);
    }
}

/**
 * @brief passes to the next turn ie changes player
 *
 */
void my_window::next_turn()
{
    // set all other buttons to false

    dessin.set_add_route_pressed(false);
    dessin.set_add_house_pressed(false);
    dessin.ReafficheDessin();

    /*----------------------First Phase ------------------*/
    if (first_turns == true)

    {
        manage_first_phase();
    }

    else if (first_turns == false)
    /*----------------------Second Phase ------------------*/
    {

        manage_second_phase();
    }
}

/**
 * @brief
 * simulate dice playing action
 * this function listen to play dice button
 */
void my_window::play_dice()
{
    if (my_dice.get_dice_state() == true)
    {
        // set all other buttons to false
        dessin.set_add_route_pressed(false);
        dessin.set_add_house_pressed(false);
        dessin.ReafficheDessin();

        this->dice_value = my_dice.randomize_dice();
        my_dice.set_dice_state(false);
        Dice_output_label.set_markup("returned value = " + to_string(dice_value));

        update_ressources(dice_value);

        dice_image = Gdk::Pixbuf::create_from_file("data/vigniettes/" + to_string(dice_value) + ".png");
        dice_image = dice_image->scale_simple((dice_image->get_height()) * 0.5, (dice_image->get_width()) * 0.5, Gdk::INTERP_BILINEAR);
        Dice_Image.set(dice_image);
    }
    else
    {
        Gtk::MessageDialog d(*this, "Can not play more than one time in a turn !!  ", true, Gtk::MESSAGE_ERROR);
        d.run();
    }

    update_resources_table();
}

/**
 * @brief opens a child window showing the rules for each construction  
 * 
 */
void my_window::see_rules()
{
    my_rules_win = new rules_win(); //init pointer
    my_rules_win->show();
    
}



//--------------------------- functions used to manage players turns-----------------------//

/**
 * @brief returns a pointer referencing the player with the given state
 *
 * @param state
 * @return Player
 */
Player *my_window::get_player_by_state(States state)
{
    vector<Player>::iterator it;
    for (it = player_list.begin(); it != player_list.end(); ++it)
    {
        if (it->get_player_STATE_id() == state)
        {
            return &(*it);
        }
    }
}

/**
 * @brief
 * updates players resources based on the dice value
 *
 * @param dice_val
 */
void my_window::update_ressources(int dice_val)
{
    vector<tuile> activated_tuiles = dessin.tuile_map.get_tuiles_by_DiceNum(dice_value);
    vector<node> all_nodes = dessin.route_map.get_all_nodes();
    for (unsigned i = 0; i < activated_tuiles.size(); i++)
    {
        cout << "activated tuiles" << activated_tuiles[i].get_id() << endl;

        for (unsigned k = 0; k < all_nodes.size(); k++)
        {
            States node_state = all_nodes[k].get_state();
            vector<tuile> node_adj_tuiles = all_nodes[k].get_ressources();

            bool element_exist = false;

            for (unsigned j = 0; j < node_adj_tuiles.size(); j++)
            {
                if (node_adj_tuiles[j].get_id() == activated_tuiles[i].get_id())
                {
                    element_exist = true;
                    break;
                };
            }

            if (element_exist && node_state != States::empty)
            {
                cout << "node state" << static_cast<int>(node_state) << endl;
                Player *player_ptr = get_player_by_state(node_state);
                player_ptr->append_to_ressources(activated_tuiles[i].get_ressource());
            }
        }
    }
}

/**
 * @brief this methode manage the first the first part of the game
 * initial phase where player have diffrent previledges and rules change
 *
 */
void my_window::manage_first_phase()
{
    update_score();

    if (
        ((current_player_itr->get_score() == 1) && (current_player_itr->get_number_of_routes() == 1) && (inversed == false)) ||
        ((current_player_itr->get_score() == 2) && (current_player_itr->get_number_of_routes() == 2) && (inversed == true)))

    {
        // check if first Phase is finished
        if ((current_player_itr == player_list.begin()) && (inversed == true))
        // set first_turn to false to begin 2nd phase in the game
        {
            first_turns = false;
            dessin.route_map.set_init_phase_off();

            // set the play dice button when first phase is over
            my_dice.set_dice_state(true);
            this->dice_value = 0; // reset dice to initial value = zero corresponding to no Tuile
            Dice_output_label.set_markup(" Throw Dice ? ? ?");

            button_play_dice.set_label("Play Dice");
            DiceGrid.attach(button_play_dice, 0, 0, 1, 1);
            button_play_dice.signal_clicked().connect(sigc::mem_fun(*this, &my_window::play_dice));
            this->show_all_children();
        }

        // first phase first sens
        if ((current_player_itr < last_elemnt) && (inversed == false))

        {
            current_player_itr = next(current_player_itr);
            dessin.setActivePlayer(&*current_player_itr);
            player_turn_label.set_markup("<b>player :" + current_player_itr->get_name() + "</b>");

            if (current_player_itr == last_elemnt)
            // // plays another time and inverse the sens
            {
                inversed = true;
                Gtk::MessageDialog d(*this, " put the image and name of the player Please add 2 houses and 4 routes ", true, Gtk::MESSAGE_ERROR);
                d.run();
            }
        }
        // first phase inverse sens
        else if ((inversed == true) && (current_player_itr > player_list.begin()))

        {

            current_player_itr = next(current_player_itr, -1);
            dessin.setActivePlayer(&*current_player_itr);
            player_turn_label.set_markup("<b>player :" + current_player_itr->get_name() + "</b>");
        }
    }
    else
    {
        Gtk::MessageDialog d(*this, "You must place 1 house and 1 Route ", true, Gtk::MESSAGE_ERROR);
        d.run();
    }

    update_score();
    update_resources_table();
}

void my_window::manage_second_phase()
{
    // reset dice parameters

    my_dice.set_dice_state(true);
    this->dice_value = 0; // reset dice to initial value = zero corresponding to no tuile
    Dice_output_label.set_markup(" Throw Dice ? ? ?");
    Dice_Image.clear();
    update_score();

    if (current_player_itr < last_elemnt)

    {
        current_player_itr = next(current_player_itr);
        dessin.setActivePlayer(&*current_player_itr); //*current_player_itr gives us the player and
        player_turn_label.set_markup("<b>player :" + current_player_itr->get_name() + "</b>");
    }
    else
    {
        current_player_itr = player_list.begin();
        dessin.setActivePlayer(&*current_player_itr); //*current_player_itr gives us the player and
        player_turn_label.set_markup("<b>player :" + current_player_itr->get_name() + "</b>");
    }
    update_score();
    update_resources_table();
}

bool my_window::get_init_inversed()
{
    return inversed ;
}

//---------------------------  functions used to set the window's widgets --------------------------//

/**
 * @brief
 * Update the score label in sidebox
 */
void my_window::update_score()
{
    States active_player_state;
    active_player_state = current_player_itr->get_player_STATE_id();
    current_player_itr->set_route_number(dessin.route_map.count_routes(active_player_state));
    current_player_itr->set_score(dessin.route_map.count_score(active_player_state));
    score_label.set_markup("<b> Score =" + to_string(current_player_itr->get_score()) + "</b>");
    this->show_all();
}





/**
 * @brief
 * updates ressources table in the sidebox
 */
void my_window::update_resources_table()
{
    /*-----------------------update resources table ----------------*/
    bois_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::bois)));
    ble_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::ble)));
    mouton_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::mouton)));
    pierre_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::pierre)));
    brick_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::argile)));
    //--------------------------------------------------------------//
}

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
    /*--------------logo------------------------*/
    logo_image = Gdk::Pixbuf::create_from_file("data/logo.png");
    logo_image = logo_image->scale_simple((logo_image->get_width()) * 0.7, (logo_image->get_height()) * 0.4, Gdk::INTERP_BILINEAR);
    Logo_Image.set(logo_image);

    /*----------------------------player box---------------------------*/
    /*---------- info frame---------------*/
    update_score();
    dessin.setActivePlayer(&*current_player_itr);
    player_turn_label.set_markup("<b> Player : " + current_player_itr->get_name() + "</b>");
    score_label.set_markup("<b> Score =" + to_string(current_player_itr->get_score()) + "</b>");

    ble_title.set_markup("Blé");
    ble_image = Gdk::Pixbuf::create_from_file("data/ressources/Ble.png");
    ble_image = ble_image->scale_simple((ble_image->get_height()) * 0.10, (ble_image->get_width()) * 0.20, Gdk::INTERP_BILINEAR);
    ble_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::ble)));
    Ble_Image.set(ble_image);

    bois_title.set_markup("Bois");
    bois_image = Gdk::Pixbuf::create_from_file("data/ressources/Bois.png");
    bois_image = bois_image->scale_simple((bois_image->get_height()) * 0.10, (bois_image->get_width()) * 0.20, Gdk::INTERP_BILINEAR);
    bois_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::bois)));
    Bois_Image.set(bois_image);

    mouton_title.set_markup("Moutons");
    mouton_image = Gdk::Pixbuf::create_from_file("data/ressources/Mouton.png");
    mouton_image = mouton_image->scale_simple((mouton_image->get_height()) * 0.10, (mouton_image->get_width()) * 0.20, Gdk::INTERP_BILINEAR);
    mouton_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::mouton)));
    Mouton_Image.set(mouton_image);

    pierre_title.set_markup("Pierre");
    pierre_image = Gdk::Pixbuf::create_from_file("data/ressources/Pierre.png");
    pierre_image = pierre_image->scale_simple((pierre_image->get_height()) * 0.10, (pierre_image->get_width()) * 0.20, Gdk::INTERP_BILINEAR);
    pierre_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::pierre)));
    Pierre_Image.set(pierre_image);

    brick_title.set_markup("Briques");
    argile_image = Gdk::Pixbuf::create_from_file("data/ressources/Brique.png");
    argile_image = argile_image->scale_simple((argile_image->get_height()) * 0.10, (argile_image->get_width()) * 0.20, Gdk::INTERP_BILINEAR);
    brick_count_label.set_markup("x" + to_string(current_player_itr->count_X_ressources(Resources::argile)));
    Argile_Image.set(argile_image);

    

    //---------------Attach element -------------------------//
    infoGrid.set_row_spacing(30);
    infoGrid.set_column_spacing(20);
    infoGrid.set_margin_left(150);
    infoGrid.set_margin_top(20);
    infoGrid.attach(player_turn_label, 0, 0, 1, 1);
    infoGrid.attach(score_label, 0, 1, 1, 1);

    ressourcesGrid.set_margin_left(100);
    ressourcesGrid.set_column_spacing(20);
    ressourcesGrid.set_row_spacing(20);

    ressourcesGrid.attach(ble_title, 0, 2, 1, 1);
    ressourcesGrid.attach(Ble_Image, 0, 3, 1, 1);
    ressourcesGrid.attach(ble_count_label, 0, 4, 1, 1);

    ressourcesGrid.attach(bois_title, 1, 2, 1, 1);
    ressourcesGrid.attach(Bois_Image, 1, 3, 1, 1);
    ressourcesGrid.attach(bois_count_label, 1, 4, 1, 1);

    ressourcesGrid.attach(mouton_title, 2, 2, 1, 1);
    ressourcesGrid.attach(Mouton_Image, 2, 3, 1, 1);
    ressourcesGrid.attach(mouton_count_label, 2, 4, 1, 1);

    ressourcesGrid.attach(pierre_title, 3, 2, 1, 1);
    ressourcesGrid.attach(Pierre_Image, 3, 3, 1, 1);
    ressourcesGrid.attach(pierre_count_label, 3, 4, 1, 1);

    ressourcesGrid.attach(brick_title, 4, 2, 1, 1);
    ressourcesGrid.attach(Argile_Image, 4, 3, 1, 1);
    ressourcesGrid.attach(brick_count_label, 4, 4, 1, 1);

    player_info_frame.set_label("Player info");
    ressouces_frame.set_label("Ressources");
    player_info_box.set_spacing(20);
    player_info_box.set_margin_bottom(20);
    player_info_box.set_margin_left(20);
    player_info_box.set_margin_bottom(20);
    player_info_box.set_margin_right(20);
    player_info_box.pack_start(infoGrid);
    ressouces_frame.add(ressourcesGrid);
    player_info_box.pack_start(ressouces_frame);
    player_info_frame.add(player_info_box);

    /*---------buttons box--------------*/

    button_house.add_label("Build a House");
    button_house.signal_clicked().connect(sigc::mem_fun(*this, &my_window::button_add_house));
    button_route.add_label("Build Route");
    button_route.signal_clicked().connect(sigc::mem_fun(*this, &my_window::button_add_route));
    button_next_turn.add_label("Next Turn");
    button_next_turn.signal_clicked().connect(sigc::mem_fun(*this, &my_window::next_turn));
    button_rules.add_label("See construction rules");
    button_rules.signal_clicked().connect(sigc::mem_fun(*this, &my_window::see_rules));
    // | //
    // v //

    buttonsGrid.set_margin_left(20);
    buttonsGrid.set_row_spacing(10);
    buttonsGrid.set_column_spacing(10);

    buttonsGrid.attach(button_house, 0, 0, 1, 1);
    buttonsGrid.attach(button_rules, 1, 0, 1, 1);
    buttonsGrid.attach(button_route, 0, 1, 1, 1);
    buttonsGrid.attach(button_next_turn, 0, 2, 1, 1);

    

    // | //
    // v //
    action_buttons_frame.set_label("Action Buttons");
    action_buttons_frame.add(buttonsGrid);

    /*---------- Dice output frame---------------*/

    /*
        Dice button
    */

    DiceGrid.set_margin_left(20);
    DiceGrid.set_row_spacing(10);
    DiceGrid.set_column_spacing(15);

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
    buttons_box.pack_start(Logo_Image, 0, 0);
    buttons_box.pack_start(player_info_frame, 0, 0);
    buttons_box.pack_start(action_buttons_frame, 0, 0);
    buttons_box.pack_start(dice_output_frame, 0, 0);

    /*---------buttons box--------------*/
}
