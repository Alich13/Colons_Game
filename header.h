#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/alignment.h>
#include <algorithm>
#include <unistd.h>
#include "board_data_structures/data_structures.h" //import the costumized data structure we will use in Board class

// this is just  class declaration that will be referenced by Dessin class before its creation 
class my_window; 
class thief_win;

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& player   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/
/**
 * @brief class player
 * We can use This class to create player instances  which will
 * have diffrent attributes as :
 *   Total ressources
 * 	 Id
 * 	 Name
 *   Total points
 */
class Player
{
public:

	States id;
	Player(States N_id, string N_nickname);
	virtual ~Player(){};
	int count_ressources(Resources ressource_we_looking_for);
	int get_player_INT_id();
	States get_player_STATE_id();
	string get_name();
	void append_to_ressources(Resources ressource);
	int count_X_ressources(Resources ressource);
	int get_number_of_routes();
	void set_route_number(int N_count);
	
	void set_resources(vector<Resources> N_ressources);
	vector<Resources> get_resources();

	int get_score();
	void set_score(int N_score);


private:
	string Nickname;
	int total_points = 0;
	int number_of_routes =0 ;
	vector<Resources> player_ressources = {};
};

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&  Board  &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/
/**
 * @brief
 * This class  contains the board elements intersections , tuiles, routes
 * these elements themselves are also classes  that contain all informations like
 * cordonates of elements ,methodes to check .
 * for example the states of different elements
 * This class uses internally the classes T_map and I_map "from data_stucture.h"
 */
class Board
{
public:
	Board();
	virtual ~Board(){};
	// I_map board_map;
	T_map tuile_map;
	I_map intersection_map;

private:
};

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& Dessin   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/
/**
 * @brief
 * This class represents the actual drawing (le dessin ) which will be included in boardBOX
 * all elements from Board will be printed here as well as all the interaction via eventbox
 * that allows us for example to place new houses or routes
 * this class inherits from DrawingArea (Abstact Class )
 */

class Dessin : public Gtk::DrawingArea
{
public:
	Dessin(my_window & W);
	virtual ~Dessin(){};

	// set up //
	void set_add_route_pressed(bool pressed) { this->add_route_pressed = pressed; };
	void set_add_house_pressed(bool pressed) { this->add_house_pressed = pressed; };
	void set_rendred_cord(int cord_x, int cord_y);

	// get_attributes //
	void affiche_rendred_cord();

	// events //
	void updateRoute(GdkEventButton *event);
	void updateHouse(GdkEventButton *event);

	// Draw Functions //
	void drawBoard(const Cairo::RefPtr<Cairo::Context> &cr);
	void draw_intersection_map(const Cairo::RefPtr<Cairo::Context> &cr);
	void drawVingnette(const Cairo::RefPtr<Cairo::Context> &cr);
	void drawRoute(const Cairo::RefPtr<Cairo::Context> &cr);

	void drawPossibleRoutes(const Cairo::RefPtr<Cairo::Context> &cr);
	void drawPossibleHouses(const Cairo::RefPtr<Cairo::Context> &cr);

	void setActivePlayer(Player *current_player);
	void ReafficheDessin();

	// set sub maps (tuiles map  et intersection map) from Board Class
	Board board;
	T_map tuile_map = board.tuile_map;
	I_map route_map = board.intersection_map;

protected:
	bool on_button_press_event(GdkEventButton *event);			 // function handles mouse events
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &); // make the drawings

private:
	my_window & my_win ;
	Player *active_player; // a pointer to the active player

	int x1, x2, y1, y2; // cordonates of points
	int cord_x = 0;
	int cord_y = 0;		  // cord to be rendred in label
	int board_x, board_y; // top right x y cordonate inside the box
	int board_width, board_height;

	bool firstclick, secondclick;
	bool add_route_pressed = false;
	bool add_house_pressed = false; // bool var telling if the button build route is pressed or not

	std::vector<int> X, Y, vx1, vy1, vx2, vy2;
	Glib::RefPtr<Gdk::Pixbuf> pic_board, house, vigniette, construction_arrow;
};

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& Dice   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/
/**
 * @brief Dice class
 * Dice_state is set to true when the player can play
 */
class Dice
{
public:
	Dice();
	virtual ~Dice(){};
	int randomize_dice();
	bool get_dice_state();
	void set_dice_state(bool new_state);

private:
	bool canPlayDice = true;
};

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& rules window   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/
/**
 * @brief 
 * 
 */
class rules_win : public Gtk::Window
{
public:
rules_win();
virtual ~rules_win(){};

protected:

Gtk::VBox mainBox ;
Gtk::Grid Rules_Grid;
Glib::RefPtr<Gdk::Pixbuf> card_image;
Gtk::Image Card_Image;
Gtk::Label lbl_;

};

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& thief window (voleur)  &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/
/**
 * @brief 
 * 
 */
class thief_win : public Gtk::Window
{
public:
thief_win(my_window & W); // set or initiate a reference to the main window in the constructor
virtual ~thief_win(){};
void set_ressources_table();
void set_player_list(vector<Player> &N_list);
void submit_choices();
void update_ressources_table();
int  update_discard_num();

vector<Resources> update_resources_list();
vector<Player> filter_8(vector<Player> input_list);

protected:

	Gtk::VBox mainBox ;
	Gtk::Grid main_Grid;
	Glib::RefPtr<Gdk::Pixbuf> px_image;
	Gtk::Image Image ;

	Gtk::Button
		button_submit ;

	Gtk::VBox
		player_info_box;
	Gtk::Label
	 	lbl_,
		lbl_1,
		lbl_2,
		
		player_turn_label,
		score_label,

		ble_title,
		bois_title,
		mouton_title,
		brick_title,
		pierre_title,

		ble_count_label,
		mouton_count_label,
		bois_count_label,
		pierre_count_label,
		brick_count_label;

	Gtk::Frame
		board_Frame,
		player_info_frame,
		ressouces_frame;

	Gtk::Grid
		mainGrid,
		infoGrid,
		Rules_Grid,
		ressourcesGrid;
	
	Glib::RefPtr<Gdk::Pixbuf>
		dice_image,
		ble_image,
		pierre_image,
		argile_image,
		mouton_image,
		bois_image,
		logo_image;

	Gtk::Image
		Dice_Image,
		Ble_Image,
		Pierre_Image,
		Argile_Image,
		Mouton_Image,
		Bois_Image,
		Logo_Image;
	Gtk::SpinButton
		spin_ble,
		spin_mouton,
		spin_pierre,
		spin_argile,
		spin_bois;
			 


private :
	
	my_window & parent_win ;
	
	// iterator inside to iterate through list of player with more than 8 cards 
	vector<Player>::iterator current_player_itr ;
	vector<Player> list_player_with_8_ressources;

};



/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& Game  window   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/
/**
 * @brief
 * This class represent the main window of the game :
 * it contains :
 * 			-/ game board (drawing)
 * 			-/ button box
 * 			-/ dé
 */
class my_window : public Gtk::Window
{
public:
	my_window();
	virtual ~my_window(){};

	void set_my_menu();
	void set_side_box();

	void button_add_house();
	void button_add_path();
	void button_add_route();

	void next_turn();
	void play_dice();
	void see_rules();

	void update_ressources(int dice_value);
	void update_resources_table();
	void update_score();

	void manage_first_phase();
	void manage_second_phase();
	bool get_init_inversed();
	void set_player_list(); // this methode will be called from main to set the number of player at the begining of the game my_window.set_player_list()
	
	Player *get_player_by_state(States state);
	void place_flag_image(int player_num ,Glib::RefPtr<Gdk::Pixbuf> px_image ,Gtk::Image*  Image , Gtk::Grid*  my_grid , int col , int row );
	void open_thief_window();

protected:
	Dessin dessin;
	Dice my_dice;

	// child windows
	rules_win *my_rules_win;
	thief_win *thief_window;

	Gtk::VBox
		mainLayout,
		board_box,
		player_info_box,
		buttons_box;

	Gtk::Label
		player_turn_label,
		Dice_output_label,
		score_label,

		ble_title,
		bois_title,
		mouton_title,
		brick_title,
		pierre_title,

		ble_count_label,
		mouton_count_label,
		bois_count_label,
		pierre_count_label,
		brick_count_label;

	Gtk::Frame
		board_Frame,
		action_buttons_frame,
		player_info_frame,
		dice_output_frame,
		ressouces_frame;
	Gtk::HButtonBox buttons_Hbox;

	Gtk::Grid
		mainGrid,
		infoGrid,
		buttonsGrid,
		DiceGrid,
		Action_grid,
		Rules_Grid,
		ressourcesGrid;
	Gtk::Button
		button_start_new_win,
		button_house,
		button_route,
		button_next_turn,
		button_play_dice,
		button_test_thief,
		button_rules ;

	Gtk::MenuBar menuBar;
	Gtk::MenuItem menuFiles;
	Gtk::Menu subMenuFiles;
	Gtk::MenuItem open, close, quit;
	Gtk::SeparatorMenuItem hline;
	Gtk::MenuItem menuEdit;
	Gtk::ScrolledWindow m_ScrolledWindow;

	Glib::RefPtr<Gdk::Pixbuf>
		px_image,
		dice_image,
		ble_image,
		pierre_image,
		argile_image,
		mouton_image,
		bois_image,
		logo_image;

	Gtk::Image
		I_image,
		Dice_Image,
		Ble_Image,
		Pierre_Image,
		Argile_Image,
		Mouton_Image,
		Bois_Image,
		Logo_Image;
		

private:
	int dice_value = 0;
	bool first_turns = false ; // for testing (normally true) 
	bool inversed = false ;
	
	//---------------- for test
	
	Player P1 = Player(States::p1, "ALi");
	Player P2 = Player(States::p2, "Louai");
	Player P3 = Player(States::p3, "jalil");
	Player P4 = Player(States::p4, "mariem");
	//--------------------set ressources for test -----------------------------// 
	

	//------------------------------------------
	vector<Player> player_list={P1, P2, P3,P4};
	vector<Player>::iterator current_player_itr = player_list.begin();
	vector<Player>::iterator last_elemnt = next(player_list.end(),-1);
};


/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& welcome window   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/

class Welcome_Window : public Gtk::Window
{
public:
	Welcome_Window();
	virtual ~Welcome_Window(){};
	void Open_New_Win_Clicked();
	void display_players_options();
	void detach_all();
	void place_flag_image( int player_num ,Glib::RefPtr<Gdk::Pixbuf> px_image ,Gtk::Image*  Image , Gtk::Grid*  my_grid , int col , int row );

protected:
	my_window *main_window;
	Gtk::Label 
		welcome_label,
		l_Entry_1,
        l_Entry_2,
        l_Entry_3,
        l_Entry_4,
        l_Entry_5,
        l_Entry_6,
		lbl_;
	Gtk::Button 
		button_start_new_win,
		button_submit_number;
	Gtk::VBox
		mainLayout;
	Gtk::Grid
		grid;
	Glib::RefPtr<Gdk::Pixbuf>
		logo,
		px_red ,
		px_blue,
		px_green ,
		px_orange ,
		px_brown,
		px_white;
	Gtk::SpinButton 
		spin;
	Gtk::Image
		Logo,
		I_red ,
		I_blue,
		I_green ,
		I_orange ,
		I_brown,
		I_white;
	
	Gtk::Entry 
        m_Entry_1,
        m_Entry_2,
        m_Entry_3,
        m_Entry_4,
        m_Entry_5,
        m_Entry_6;



};



#endif // GTKMM_EXAMPLE_MYAREA_H
