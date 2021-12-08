#include "../header.h"

Welcome_Window::Welcome_Window()
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
    context->add_class("welcome_window");

    this->set_title("welcome to colons de catanes game");
    this->set_position(Gtk::WIN_POS_CENTER);
    this->set_default_size(800, 400); //+5 size of all the window for the border	
    set_border_width(5);
    /*--------------logo------------------------*/
    logo = Gdk::Pixbuf::create_from_file("data/logo.png");
    logo = logo->scale_simple((logo->get_width()) * 0.5,(logo->get_height()) * 0.4, Gdk::INTERP_BILINEAR);
    Logo.set(logo);
    /*------------------------------------------*/
    grid.set_column_spacing(20);
    grid.set_row_spacing(50);
    grid.set_margin_left(100);

    /*-------------Spin----------------------------*/
    
    lbl_.set_label("Chose  number of players :");
    spin.set_range(2,6);
    spin.set_value(3);
    spin.set_increments(1,1);
    

    button_submit_number.add_label("Go");
    button_submit_number.signal_clicked().connect(sigc::mem_fun(*this, &Welcome_Window::display_players_options));
    button_start_new_win.add_label("Start Game");
    button_start_new_win.signal_clicked().connect(sigc::mem_fun(*this, &Welcome_Window::Open_New_Win_Clicked));
    
    grid.attach(lbl_,0,0,1,1);
    grid.attach(spin,1,0,1,1);
    grid.attach(button_submit_number,2,0,1,1);
    
    
    mainLayout.pack_start(Logo);
    mainLayout.pack_start(grid);
    this->add(mainLayout);
    this->show_all_children();
	};



void Welcome_Window::display_players_options()
{
    int num_players = spin.get_value();
    

    m_Entry_1.set_max_length(10);
    m_Entry_2.set_max_length(10);
    m_Entry_3.set_max_length(10);
    m_Entry_4.set_max_length(10); 
    m_Entry_5.set_max_length(10);
    m_Entry_6.set_max_length(10);

    l_Entry_1.set_label("Enter player 1 name ");
    l_Entry_2.set_label("Enter player 2 name ");
    l_Entry_3.set_label("Enter player 3 name ");
    l_Entry_4.set_label("Enter player 4 name ");
    l_Entry_5.set_label("Enter player 5 name ");
    l_Entry_6.set_label("Enter player 6 name ");

    switch (num_players)  {

    case 2:
        detach_all();

        grid.attach(l_Entry_1,0,1,1,1);
        grid.attach(m_Entry_1,1,1,1,1);
        place_flag_image(1,px_blue,&I_blue ,&grid,2,1);

        grid.attach(l_Entry_2,0,2,1,1);
        grid.attach(m_Entry_2,1,2,1,1);
        place_flag_image(2,px_red,&I_red ,&grid,2,2);
        
        grid.attach(button_start_new_win,1,3,1,1);
        break;

    case 3:
        detach_all();
        grid.attach(l_Entry_1,0,1,1,1);
        grid.attach(m_Entry_1,1,1,1,1);
        place_flag_image(1,px_blue,&I_blue ,&grid,2,1);

        grid.attach(l_Entry_2,0,2,1,1);
        grid.attach(m_Entry_2,1,2,1,1);
        place_flag_image(2,px_red,&I_red ,&grid,2,2);

        grid.attach(l_Entry_3,0,3,1,1);
        grid.attach(m_Entry_3,1,3,1,1);
        place_flag_image(3,px_green,&I_green ,&grid,2,3);
        
        grid.attach(button_start_new_win,1,4,1,1);
        break;

    case 4:
        detach_all();
      
        grid.attach(l_Entry_1,0,1,1,1);
        grid.attach(m_Entry_1,1,1,1,1);
        place_flag_image(1,px_blue,&I_blue ,&grid,2,1);

        grid.attach(l_Entry_2,0,2,1,1);
        grid.attach(m_Entry_2,1,2,1,1);
        place_flag_image(2,px_red,&I_red ,&grid,2,2);

        grid.attach(l_Entry_3,0,3,1,1);
        grid.attach(m_Entry_3,1,3,1,1);
        place_flag_image(3,px_green,&I_green ,&grid,2,3);

        grid.attach(l_Entry_4,0,4,1,1);
        grid.attach(m_Entry_4,1,4,1,1);
        place_flag_image(4,px_orange,&I_orange ,&grid,2,4);

        grid.attach(button_start_new_win,1,5,1,1);
        break;
    
    case 5:
        detach_all();
      
        grid.attach(l_Entry_1,0,1,1,1);
        grid.attach(m_Entry_1,1,1,1,1);
        place_flag_image(1,px_blue,&I_blue ,&grid,2,1);

        grid.attach(l_Entry_2,0,2,1,1);
        grid.attach(m_Entry_2,1,2,1,1);
        place_flag_image(2,px_red,&I_red ,&grid,2,2);

        grid.attach(l_Entry_3,0,3,1,1);
        grid.attach(m_Entry_3,1,3,1,1);
        place_flag_image(3,px_green,&I_green ,&grid,2,3);

        grid.attach(l_Entry_4,0,4,1,1);
        grid.attach(m_Entry_4,1,4,1,1);
        place_flag_image(4,px_orange,&I_orange ,&grid,2,4);

        grid.attach(l_Entry_5,0,5,1,1);
        grid.attach(m_Entry_5,1,5,1,1);
        place_flag_image(5,px_brown,&I_brown ,&grid,2,5);

        grid.attach(button_start_new_win,1,6,1,1);
        break;


    
    case 6:
        detach_all();
      
        grid.attach(l_Entry_1,0,1,1,1);
        grid.attach(m_Entry_1,1,1,1,1);
        place_flag_image(1,px_blue,&I_blue ,&grid,2,1);

        grid.attach(l_Entry_2,0,2,1,1);
        grid.attach(m_Entry_2,1,2,1,1);
        place_flag_image(2,px_red,&I_red ,&grid,2,2);

        grid.attach(l_Entry_3,0,3,1,1);
        grid.attach(m_Entry_3,1,3,1,1);
        place_flag_image(3,px_green,&I_green ,&grid,2,3);

        grid.attach(l_Entry_4,0,4,1,1);
        grid.attach(m_Entry_4,1,4,1,1);
        place_flag_image(4,px_orange,&I_orange ,&grid,2,4);

        grid.attach(l_Entry_5,0,5,1,1);
        grid.attach(m_Entry_5,1,5,1,1);
        place_flag_image(5,px_brown,&I_brown ,&grid,2,5);

        grid.attach(l_Entry_6,0,6,1,1);
        grid.attach(m_Entry_6,1,6,1,1);
        place_flag_image(6,px_white,&I_white ,&grid,2,6);

        grid.attach(button_start_new_win,1,7,1,1);
        break;

    default:
        Gtk::MessageDialog d(*this, "Please chose a number between 2 and 6 ", true, Gtk::MESSAGE_INFO);
        d.run();
    }


    
    this->show_all_children();

}



void Welcome_Window::Open_New_Win_Clicked()
{
    int num_players = spin.get_value();
    
    
    
    if (num_players == 2)
    {
        Player P1 = Player(States::p1, m_Entry_1.get_text());
	    Player P2 = Player(States::p2, m_Entry_2.get_text());
        vector<Player> player_list={P1, P2};
        main_window = new my_window(player_list);

    }


    if (num_players == 3)
    {
        Player P1 = Player(States::p1, m_Entry_1.get_text());
	    Player P2 = Player(States::p2, m_Entry_2.get_text());
    	Player P3 = Player(States::p3, m_Entry_3.get_text());
	    

        vector<Player> player_list={P1, P2 ,P3};
        main_window = new my_window(player_list);
    }


    if (num_players == 4)
    {
        Player P1 = Player(States::p1, m_Entry_1.get_text());
	    Player P2 = Player(States::p2, m_Entry_2.get_text());
        Player P3 = Player(States::p3, m_Entry_3.get_text());
	    Player P4 = Player(States::p4, m_Entry_4.get_text());

        vector<Player> player_list={P1, P2 ,P3,P4};
        main_window = new my_window(player_list);
    }


    if (num_players == 5)
    {
        Player P1 = Player(States::p1, m_Entry_1.get_text());
	    Player P2 = Player(States::p2, m_Entry_2.get_text());
        Player P3 = Player(States::p3, m_Entry_3.get_text());
	    Player P4 = Player(States::p4, m_Entry_4.get_text());
        Player P5 = Player(States::p5, m_Entry_5.get_text());

        vector<Player> player_list={P1, P2 ,P3,P4,P5};
        main_window = new my_window(player_list);
	
    }



    if (num_players == 6)
    {
        Player P1 = Player(States::p1, m_Entry_1.get_text());
	    Player P2 = Player(States::p2, m_Entry_2.get_text());
        Player P3 = Player(States::p3, m_Entry_3.get_text());
	    Player P4 = Player(States::p4, m_Entry_4.get_text());
        Player P5 = Player(States::p5, m_Entry_5.get_text());
        Player P6 = Player(States::p6, m_Entry_6.get_text());
    
        vector<Player> player_list={P1, P2 ,P3,P4,P5 ,P6};
        main_window = new my_window(player_list);
    }

    
    main_window->show();
    button_submit_number.hide();
    button_start_new_win.hide();

    
    
}

void Welcome_Window::detach_all()
{
    grid.remove(m_Entry_1);
    grid.remove(m_Entry_2);
    grid.remove(m_Entry_3);
    grid.remove(m_Entry_4);
    grid.remove(m_Entry_5);
    grid.remove(m_Entry_6);

    grid.remove(l_Entry_1);
    grid.remove(l_Entry_2);
    grid.remove(l_Entry_3);
    grid.remove(l_Entry_4);
    grid.remove(l_Entry_5);
    grid.remove(l_Entry_6);

    grid.remove(I_white);
    grid.remove(I_blue);
    grid.remove(I_red);
    grid.remove(I_green);
    grid.remove(I_brown);
    grid.remove(I_orange);

    grid.remove(button_start_new_win);


    this->show_all_children();
}
/**
 * @brief places the flags images 
 * 
 * @param player_num  number of the player 
 * @param px_image    pixbuff image object
 * @param Image       Gtk:: Image object
 * @param my_grid     the gird in which we want to attach our images
 * @param col         the colon in the given grid
 * @param row           the row in the given grid
 */
void Welcome_Window::place_flag_image(int player_num ,Glib::RefPtr<Gdk::Pixbuf> px_image ,Gtk::Image*  Image , Gtk::Grid*  my_grid , int col , int row )
{

    px_image = Gdk::Pixbuf::create_from_file("data/flags/" + to_string(player_num) +".png");
    px_image = px_image->scale_simple((px_image->get_height()) * 0.5, (px_image->get_width()) * 0.5, Gdk::INTERP_BILINEAR);
    Image->set(px_image);
    my_grid->attach(*Image, col,row , 1, 1);
}
