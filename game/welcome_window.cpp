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
    grid.set_row_spacing(20);
    grid.set_margin_left(100);

    /*-------------combobox----------------------------*/
    
    //Fill the combo:
    c.append("something");
    c.append("something else");
    c.append("something or other");
    c.set_active(1);

    lbl_.set_label("Colons de Catanes");
    button_start_new_win.add_label("Start Game");
    button_start_new_win.signal_clicked().connect(sigc::mem_fun(*this, &Welcome_Window::Open_New_Win_Clicked));
    grid.attach(lbl_,0,0,1,1);
    grid.attach(c,0,1,1,1);
    grid.attach(button_start_new_win,0,2,1,1);
    mainLayout.pack_start(Logo);
    mainLayout.pack_start(grid);
    this->add(mainLayout);
    this->show_all_children();
	};



void Welcome_Window::Open_New_Win_Clicked()
{

    main_window = new my_window();
    
    /*
    
        all settings to pass to  mainwindow
        main_window.set_players
    
    */

    main_window->show();
    button_start_new_win.hide();
    
}