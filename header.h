#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/alignment.h>
#include <algorithm>
#include <unistd.h>
#include "board_data_structures/data_structures.h" //import the costumized data structure we will use in Board class

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& player   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/
class Player
{
public:
	States id;
	//------------------methodes---------------------------------------//
	Player(States N_id, string N_nickname);
	int count_ressources(Resources ressource_we_looking_for); /////!!!!
	int get_player_INT_id();
	States get_player_STATE_id();
	string get_name();
	void append_to_ressources( Resources ressource);
	int count_X_ressources(Resources ressource);

private:
	string Nickname;
	int total_points = 0;
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
 */
class Dessin : public Gtk::DrawingArea
{
public:
	Board board;
	// set sub maps (tuiles map  et intersection map)
	T_map tuile_map = board.tuile_map;
	I_map route_map = board.intersection_map;


	Dessin();
	//~Dessin();

	// set up //
	void set_add_route_pressed(bool pressed) { this->add_route_pressed = pressed; };
	void set_add_house_pressed(bool pressed) { this->add_house_pressed = pressed; };
	void set_rendred_cord(int cord_x, int cord_y)
	{
		this->cord_x = cord_x;
		this->cord_y = cord_y;
	};

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
	void drawPossibleRoute(const Cairo::RefPtr<Cairo::Context> &cr);
	void drawHouse(const Cairo::RefPtr<Cairo::Context> &cr);
	void setActivePlayer(Player *current_player);
	void ReafficheDessin();

protected:
	bool on_button_press_event(GdkEventButton *event);			 // function handles mouse events
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &); // make the drawings

private:
	
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
	Glib::RefPtr<Gdk::Pixbuf> pic_board, pic2, vigniette, construction;
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
	Dice() { ; };
	int randomize_dice()
	{
		random_device rd;
		unsigned long seed = rd();
		mt19937 engine(seed);
		discrete_distribution<int> distribution{0, 0, 2, 3, 3, 3, 3, 4, 3, 3, 3, 3, 2};
		return distribution(engine);
	}
	bool get_dice_state() { return canPlayDice; };
	void set_dice_state(bool new_state) { this->canPlayDice = new_state; };

private:
	bool canPlayDice = true;
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
	void button_add_house();
	void button_add_path();
	void button_add_route();
	void next_turn();
	void play_dice();
	void diplay_dice_visual_effect(int dice_num);
	void update_ressources(int dice_value);
	void update_resources_table();
	//-------------------
	void set_player_list(); // this methode will be called from main to set the number of player at the begining of the game
							// my_window.set_player_list()
	Player* get_player_by_state(States state);


protected:
	Dessin dessin;
	
	Dice my_dice;

	// for test
	Player P1 = Player(States::p1, "ALi");
	Player P2 = Player(States::p2, "Louai");
	Player P3 = Player(States::p3, "jalil");
	//

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
		ressourcesGrid;
	Gtk::Button
		button_start_new_win,
		button_house,
		button_route,
		button_next_turn,
		button_play_dice;

	Gtk::MenuBar menuBar;
	Gtk::MenuItem menuFiles;
	Gtk::Menu subMenuFiles;
	Gtk::MenuItem open, close, quit;
	Gtk::SeparatorMenuItem hline;
	Gtk::MenuItem menuEdit;
	Gtk::ScrolledWindow m_ScrolledWindow;
	
	Glib::RefPtr<Gdk::Pixbuf>
		dice_image,
		ble_image,
		pierre_image,
		argile_image,
		mouton_image,
		bois_image;
		
	Gtk::Image
		Dice_Image,
		Ble_Image,
		Pierre_Image,
		Argile_Image,
		Mouton_Image,
		Bois_Image;
		

private:
	int dice_value = 0;
	void set_my_menu();
	void set_side_box();
	vector<Player> player_list = {P1, P2, P3};
	vector<Player>::iterator current_player_itr = player_list.begin();
	
};


/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& welcome window   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/

class AboutWindow : public Gtk::Window
{
public:
    AboutWindow();
    virtual ~AboutWindow(){};
	void Open_New_Win_Clicked();
protected:
	my_window* main_window ;
    Gtk::Label lbl_;
	Gtk::Button button_start_new_win;
	Gtk::Grid grid;
};


#endif // GTKMM_EXAMPLE_MYAREA_H
