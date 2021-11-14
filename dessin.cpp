#include "header.h"
#include <cairomm/context.h>
#include <iostream>
#include <string> // for string class
#define SCALE 1.25
using namespace std;

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& Dessin   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/

//---------------------------------- constructeur----------------------------------//

Dessin::Dessin()
{

	//  Load images
	pic_board = Gdk::Pixbuf::create_from_file("data/Board_org.png");
	pic2 = Gdk::Pixbuf::create_from_file("data/scarabine.png");
	pic_board = pic_board->scale_simple((pic_board->get_height()) * 0.20, (pic_board->get_width()) * 0.20, Gdk::INTERP_BILINEAR); // scale image
	pic2 = pic2->scale_simple((pic2->get_height()) * 0.10, (pic2->get_width()) * 0.25, Gdk::INTERP_BILINEAR);					  // scale image
	// Set masks for mouse events
	add_events(Gdk::BUTTON_PRESS_MASK);

	// setting attributes value
	firstclick = false;
	secondclick = false;
	board_x = 100; // top right x cordonate inside the box
	board_y = 50;  // top right y cordonate inside the box
	board_width = 1000;
	board_height = 900; // same as the size of the box
}

//----------------------------------On draw----------------------------------//

bool Dessin::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{


	Gtk::Allocation allocation = get_allocation();
	// add board image //
	drawBoard(cr);
	// add vignettes
	drawVingnette(cr);

	// draw possible line
	if (add_route_pressed)
	{
		drawPossibleRoute(cr);
	}
	// if (add_house_pressed)
	// {

	// }
	
	// draw lines using mouse//
	drawRoute(cr);
	// draw nodes (houses) with active state
	draw_intersection_map(cr);
	// add elements scarabines //
	drawHouse(cr);

	return true;
}

//---------------------------------- Mouse button press handling ----------------------------------//

bool Dessin::on_button_press_event(GdkEventButton *event)
{
	// save selected pressed
	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 1))
	{
		set_rendred_cord(event->x, event->y);
		ReafficheDessin();
	}

	if (add_route_pressed)
	{
		updateRoute(event);
	}

	if (add_house_pressed)
	{
		updateHouse(event);
	}
	return true;
}

//---------------------------------------events-------------------------------------------------------//

void Dessin::updateRoute(GdkEventButton *event)
{
	// Check if the event is a left(1) button click.
	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 1))
	{
		int selectedRoute_id = route_map.render_route(cord_x, cord_y);
		cout << "selected route " << selectedRoute_id << endl;
		if (route_map.check_possible_route(selectedRoute_id, States::p1)) //  if route constuction is possible
		{
			route_map.update_route_state(selectedRoute_id, States::p1);
			set_add_route_pressed(false);
			ReafficheDessin();
		}
		else
		{
			cout << "route construction not possible" << endl;
			set_add_route_pressed(false);
			ReafficheDessin();
		}
	}
}

void Dessin::updateHouse(GdkEventButton *event)
{
	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 1))
	{
		int selectedHouse_id = route_map.render_node(cord_x, cord_y, 10);
		cout << "selected house " << selectedHouse_id << endl;
		//cout << route_map.check_house_construction_possible(selectedHouse_id,States::p1) << endl;
		cout << "selected house " << selectedHouse_id << endl;
		if (route_map.check_house_construction_possible(selectedHouse_id,States::p1))
		{
			route_map.update_intersection_state(selectedHouse_id,States::p1);
			set_add_house_pressed(false);
			ReafficheDessin();
		}	
		else
		{
			cout << " House construction not possible " << endl;
			set_add_house_pressed(false);
			ReafficheDessin();
		}
	
		
	}
}

//-----------------------------draw Functions-----------------------------------------//

void Dessin::drawBoard(const Cairo::RefPtr<Cairo::Context> &cr)
{
	Gdk::Cairo::set_source_pixbuf(cr, pic_board, board_x, board_y); //(wifth, hight)
	cr->save();
	cr->rectangle(0, 0, board_width, board_height); // on ne peut pas suprimer
	cr->fill();
	cr->restore();
}

void Dessin::drawHouse(const Cairo::RefPtr<Cairo::Context> &cr)
{
	for (int i = 0; i < X.size(); i++)
	{
		cr->save();
		Gdk::Cairo::set_source_pixbuf(cr, pic2, X[i] - 50, Y[i] - 50);
		cr->rectangle(0, 0, board_width, board_height);
		cr->fill();
		cr->restore();
	}
}

void Dessin::drawVingnette(const Cairo::RefPtr<Cairo::Context> &cr)
{
	string vingnette_path, thief_vignette_path;
	string tuile_de_num;
	// T_map tuile_map = board.tuile_map;
	for (int i = 2; i < tuile_map.size; i++)
	{
		tuile_de_num = to_string(tuile_map.get_tuile_de_num(i));
		vingnette_path = "data/vigniettes/" + tuile_de_num + ".png";
		vigniette = Gdk::Pixbuf::create_from_file(vingnette_path);
		vigniette = vigniette->scale_simple((vigniette->get_height()) * 0.4, (vigniette->get_width()) * 0.4, Gdk::INTERP_BILINEAR);
		cr->save();
		Gdk::Cairo::set_source_pixbuf(cr, vigniette, tuile_map.get_tuile_x(i) - 20, tuile_map.get_tuile_y(i) - 20);
		cr->rectangle(0, 0, board_width, board_height);
		cr->fill();
		cr->restore();
	}

	thief_vignette_path = "data/vigniettes/thief.png";
	vigniette = Gdk::Pixbuf::create_from_file(thief_vignette_path);
	vigniette = vigniette->scale_simple((vigniette->get_height()) * 0.4, (vigniette->get_width()) * 0.4, Gdk::INTERP_BILINEAR);
	tuile thief = tuile_map.get_thief();
	cr->save();
	Gdk::Cairo::set_source_pixbuf(cr, vigniette, thief.get_x() - 20, thief.get_y() - 20);
	cr->rectangle(0, 0, board_width, board_height);
	cr->fill();
	cr->restore();
}

void Dessin::drawPossibleRoute(const Cairo::RefPtr<Cairo::Context> &cr)

{
	vector<route> all_routes = route_map.get_all_possible_routes(States::p1);
	int X1, Y1, X2, Y2;
	for (int i = 0; i < all_routes.size(); i++)
	{
		X1 = all_routes[i].get_pos1().get_x();
		Y1 = all_routes[i].get_pos1().get_y();
		X2 = all_routes[i].get_pos2().get_x();
		Y2 = all_routes[i].get_pos2().get_y();

		cr->set_line_width(5);
		cr->set_source_rgba(183, 183, 175, 0.6);
		// cr->set_source_rgba(1, 0.2, 0.2, 0.6);
		cr->move_to(X1, Y1);
		cr->line_to(X2, Y2);
		cr->stroke();
	}
}

void Dessin::draw_intersection_map(const Cairo::RefPtr<Cairo::Context> &cr)
{
	vector<node> all_nodes = route_map.get_all_nodes();
	int X, Y; // cordonates

	for (int i = 0; i < all_nodes.size(); i++)
	{

		if (all_nodes[i].get_state() != States::empty)
		{ ////********** must change later with player
			X = all_nodes[i].get_x();
			Y = all_nodes[i].get_y();
			cr->save();
			Gdk::Cairo::set_source_pixbuf(cr, pic2, X - 25, Y - 35);
			cr->rectangle(0, 0, board_width, board_height);
			cr->fill();
			cr->restore();
		}
	}
}

void Dessin::drawRoute(const Cairo::RefPtr<Cairo::Context> &cr)
{
	// we need to  do a for loop for all player after
	vector<route> all_routes_occupied_by_player = route_map.get_all_occupied_routes(States::p1);

	for (int i = 0; i < all_routes_occupied_by_player.size(); i++)
	{
		int pos1_x = all_routes_occupied_by_player[i].get_pos1().get_x();
		int pos1_y = all_routes_occupied_by_player[i].get_pos1().get_y();
		int pos2_x = all_routes_occupied_by_player[i].get_pos2().get_x();
		int pos2_y = all_routes_occupied_by_player[i].get_pos2().get_y();

		// don't put save here
		cr->set_line_width(6);
		cr->set_source_rgb(0, 0, 0);
		cr->move_to(pos1_x, pos1_y);
		cr->line_to(pos2_x, pos2_y);
		cr->stroke();
	}
}

//---------------------------------- Reaffiche----------------------------------//

void Dessin::ReafficheDessin()
{
	auto win = get_window();
	if (win)
	{
		Gdk::Rectangle r(0, 0, board_width, board_height); // je touche un mon dessin et donc ça permet de redessiner
		win->invalidate_rect(r, false);
		// win->invalidate(false);
	}
}

