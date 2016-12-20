#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <cmath>

enum KEYS{A,D,SPACE,P,E}; //nazywaM keysy bo bedzie ciezko zapamietac z tablicy co jest czym

int main(void)
{
																		//INICJACJE MODU£ÓW


	al_init();
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//DEKLAROWANIE ZMIENNYCH C

	int i=1;
	int szerokosc = 1920;
	int wysokosc = 1080;

	int klatkowe_start = 0;

	float mysz_x=szerokosc/2;
	float mysz_y=wysokosc/2;

	float kat_strzalu = 0;
	float naciag_x = 0;
	float naciag_y = 0;


	int kamera_x = 0;

	int czas_po_utracie_zycia = 60;
	int czas_po_utracie_zycia_wroga = 35;


	int zegarek = 0;
	int zegarek_animacja_boh = 0;
	int zegarek_atak = 0;
	int zegarek_strzala = 0;

	int grawitacja = 15;
	int przycisk = 0;

	bool done = false;
	bool przerys = true;
	bool skok = false;
	bool start = false;
	bool smierc = false;
	bool dotyka_gruntu = false;
	bool czy_skonczyc_skok = false;
	bool czy_bohater_biegnie = false;
	bool czy_bohater_wzlatuje = false;
	bool czy_bohater_spada = false;
	bool czy_bohater_atakuje = false;
	bool czy_bohater_naciaga = false;
	bool ruchAD = false;

	bool czy_strzala_leci = false;
	bool strzal_lewo = false;
	bool strzal_prawo = false;


	bool sciezka_w1 = false;
	bool sciezka_w2 = false;

	int pos_x = 10;
	int pos_y = (wysokosc*3)/4;

	int kolider_w1=0;
	int kolider_w2=0;

	int ilosc_zyc = 3;
	int zycie_w1 = 2;
	int zycie_w2 = 2;
	bool czy_wrog1_martwy = false;
	bool czy_wrog2_martwy = false;

	int kolider_x = pos_x;
	int kolider_y = pos_y;

	int FPS = 60;
	int ostatni_ruch = 0;

	int grunt1_x = 0;
	int grunt1_y = pos_y + 80;

	int strzala_x=0;
	int strzala_y=0;
	int strzala_g = 0;



	bool keys[5] = { false,false, false,false,false};//bo ich nie trzymasz


 //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//DEKLARACJA ZMNIENNYCH ALLEGRO


	ALLEGRO_DISPLAY *okno = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	ALLEGRO_BITMAP *bohater = NULL;
	ALLEGRO_BITMAP *ruch_boh1 = NULL;
	ALLEGRO_BITMAP *ruch_boh2 = NULL;
	ALLEGRO_BITMAP *atak = NULL;
	ALLEGRO_BITMAP *skok_gora = NULL;
	ALLEGRO_BITMAP *skok_dol = NULL;

	ALLEGRO_BITMAP *grunt1 = NULL;

	ALLEGRO_BITMAP *wrog1 = NULL;
	ALLEGRO_BITMAP *wrog2 = NULL;

	ALLEGRO_BITMAP *tlo_gl = NULL;
	ALLEGRO_BITMAP *tlo2 = NULL;

	ALLEGRO_BITMAP *strzala = NULL;
	ALLEGRO_BITMAP *zycie = NULL;
	ALLEGRO_BITMAP *tytul = NULL;
	ALLEGRO_BITMAP *tytul1 = NULL;
	ALLEGRO_BITMAP *tytul2 = NULL;
	ALLEGRO_BITMAP *tytul3 = NULL;
	ALLEGRO_BITMAP *smierc2 = NULL;
	ALLEGRO_BITMAP *zycie_zielone = NULL;
	ALLEGRO_BITMAP *zycie_czerwone = NULL;
	ALLEGRO_BITMAP *naciag = NULL;


	ALLEGRO_FONT *font18 = al_load_ttf_font("verdana.ttf", 18, 0);


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//TESTY INICJACJI



	if (!al_init())
		return -1;

	okno = al_create_display(szerokosc, wysokosc);

	if (!okno)
		return -1;


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//PRZYPISYWANIE BITMAP


	bohater = al_load_bitmap("player model.png");
	grunt1 = al_load_bitmap("grunt1.png");
	wrog1 = al_load_bitmap("wrog.png");
	wrog2 = al_load_bitmap("wrog.png");
	tlo_gl = al_load_bitmap("tlo_gl.png");
	tlo2 = al_load_bitmap("tlo2.png");
	zycie = al_load_bitmap("zycie.png");
	tytul = al_load_bitmap("tytul.png");
	tytul1 = al_load_bitmap("tytul1.png");
	tytul2 = al_load_bitmap("tytul2.png");
	tytul3 = al_load_bitmap("tytul3.png");
	zycie_zielone = al_load_bitmap("zycie_zielone.png");
	zycie_czerwone = al_load_bitmap("zycie_czerwone.png");
	ruch_boh1 = al_load_bitmap("ruch1.png");
	ruch_boh2 = al_load_bitmap("ruch2.png");
	atak = al_load_bitmap("atak.png");
	skok_gora = al_load_bitmap("skok_gora.png");
	skok_dol = al_load_bitmap("skok_dol.png");
	strzala = al_load_bitmap("strzala.png");
	naciag = al_load_bitmap("naciag.png");

	smierc2 = al_load_bitmap("tytul_smierc.png");





//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//ZDARZENIA I TIMERY


	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(okno));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//G£ÓWNA PÊTLA
																			//START


	while (start!=true)
	{
		ALLEGRO_EVENT start1;
		al_wait_for_event(event_queue, &start1);

		if (start1.type == ALLEGRO_EVENT_KEY_UP)//esc wylacza okno
		{
			switch (start1.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				start = true;
				break;
			case ALLEGRO_KEY_SPACE:
				start = true;
				break;
			}
		}

		klatkowe_start=klatkowe_start+2;


		if ((klatkowe_start >= 0) && (klatkowe_start < 240))
		{
			al_draw_bitmap(tytul1, 0, 0, 0);
		}
		if ((klatkowe_start >= 240) && (klatkowe_start < 480))
		{
			al_draw_bitmap(tytul3, 0, 0, 0);
		}
		if ((klatkowe_start >= 480) && (klatkowe_start < 720))
		{
			al_draw_bitmap(tytul2, 0, 0, 0);
		}
		if ((klatkowe_start >= 720) && (klatkowe_start < 960))
		{
			al_draw_bitmap(tytul3, 0, 0, 0);
		}


		if (klatkowe_start == 960)
		{
			klatkowe_start = 0;
		}

		al_flip_display();
	}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//PÊTLA W£ASCIWA


	while (!smierc)
	{

		while (!done)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);




			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_A:
					keys[A] = true;
					ostatni_ruch = 1;
					czy_bohater_biegnie = true;
					break;

				case ALLEGRO_KEY_D:
					keys[D] = true;
					ostatni_ruch = 0;
					czy_bohater_biegnie = true;
					break;

				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = true;
					break;

				case ALLEGRO_KEY_E:
					if ((czy_bohater_spada == false) && (czy_bohater_wzlatuje==false))
					{
						keys[E] = true;
						czy_bohater_naciaga = true;
						if (ostatni_ruch == 0)
						{
							strzal_prawo = true;
							strzal_lewo = false;
						}
						else
						{
							strzal_prawo = false;
							strzal_lewo = true;
						}
					}
					break;

				case ALLEGRO_KEY_P:
					if ((czy_bohater_spada == false) && (czy_bohater_wzlatuje==false))
					{
						keys[P] = true;
						czy_bohater_atakuje = true;
					}
					break;
				}
			}

			else if (ev.type == ALLEGRO_EVENT_KEY_UP)//esc wylacza okno
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_A:
					if (keys[A] == true)
					{
						czy_bohater_biegnie = false;

					}
						keys[A] = false;
					break;

				case ALLEGRO_KEY_D:
					if (keys[D] == true)
					{
						czy_bohater_biegnie = false;
					}
						keys[D] = false;
					break;

				case ALLEGRO_KEY_E:
					if (keys[E] == true)
					{
						czy_strzala_leci = true;
						strzala_x = pos_x;
						strzala_y = pos_y;
						strzala_g = 0;

						//NACI¥G £UKU

						if ((mysz_x - pos_x <= 400) && (mysz_x - pos_x >= -400))
						{
							naciag_x = (mysz_x - pos_x);
						}
						else
						{
							naciag_x = 400;
						}

						if ((mysz_y - pos_y <= 400) && (mysz_y - pos_y >= -400))
						{
							naciag_y = (mysz_y - pos_y);
						}
						else
						{
							naciag_y = 400;
						}
					}
					czy_bohater_naciaga = false;
						keys[E] = false;
					break;

				case ALLEGRO_KEY_ESCAPE:
					smierc = true;
					done = true;
					break;
				}
			}
			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)//X wylacza okno
			{
				done = true;
			}

//=======================================================================================================================================//
																		//STRZALA

			else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
			{
				mysz_x = ev.mouse.x;
				mysz_y = ev.mouse.y;
			}



//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//TIMER


			else if (ev.type == ALLEGRO_EVENT_TIMER)
			{


				if ((pos_y - 66 > 1080) || (ilosc_zyc == -1))
				{
					done = true;
				}

				if (sciezka_w1 == false)
				{
					kolider_w1 += 1;
					if (kolider_w1 == 30)
					{
						sciezka_w1 = true;
					}
				}
				else
				{
					kolider_w1 -= 1;
					if (kolider_w1 == 0)
					{
						sciezka_w1 = false;
					}
				}


				if (sciezka_w2 == false)
				{
					kolider_w2 += 1;
					if (kolider_w2 == 60)
					{
						sciezka_w2 = true;
					}
				}
				else
				{
					kolider_w2 -= 1;
					if (kolider_w2 == 0)
					{
						sciezka_w2 = false;
					}
				}
				przycisk = pos_x;

				if (pos_x < 960)
				{
					if (!(((pos_x <= 0) && (pos_x + 41 >= -50))))
					{
						pos_x -= keys[A] * 5;
					}
					pos_x += keys[D] * 5;
					kolider_x = pos_x;

					//fix klawiszy
					if ((przycisk - pos_x) > 0)
					{
						ostatni_ruch = 1;
						czy_bohater_biegnie = true;
					}
					if ((przycisk - pos_x) < 0)
					{
						ostatni_ruch = 0;
						czy_bohater_biegnie = true;
					}
				}

				

				else if (kamera_x == 0)
				{
					pos_x = 955;
					kolider_x = pos_x;
				}

				if (pos_x >= 960)
				{
					przycisk = kamera_x;

//=============================================================================================================//
					//KOLIDERY SCIANY OD LEWEJ

					if (!( ((kolider_x + 83 + 5 >= 850) && (kolider_x + 41 <= 1000) && (pos_y > 822))
						|| ((kolider_x + 83 + 5 >= 2440) && (kolider_x + 41 <= 3000) && (pos_y > 822))
						|| ((kolider_x + 83 + 5 >= 3235) && (kolider_x + 41 <= 4000) && (pos_y > 777))
						|| ((kolider_x + 83 + 5 >= 4130) && (kolider_x + 41 <= 4500) && (pos_y > 867))))
					{
						kolider_x += keys[D] * 5;
						kamera_x -= keys[D] * 5;
					}

//------------------------------------------------------------------------------------------------------------//
					//KOLIDERY SCIANY OD PRAWEJ

					if (!( ((kolider_x <= 1645) && (kolider_x + 41 >= 1000) && (pos_y > 822))
						|| ((kolider_x <= 4030) && (kolider_x + 41 >= 3500) && (pos_y > 777))
						|| ((kolider_x <= 4925) && (kolider_x + 41 >= 4500) && (pos_y > 867))))
					{
						kamera_x += keys[A] * 5;
						kolider_x -= keys[A] * 5;
					}

					//fix dwoch klawiszy
					if ((przycisk - kamera_x) < 0)
					{
						ostatni_ruch = 1;
						czy_bohater_biegnie = true;
					}
					if ((przycisk - kamera_x) > 0)
					{
						ostatni_ruch = 0;
						czy_bohater_biegnie = true;
					}
				}


//=======================================================================================================================================//
																	//SKOK


				if ((keys[SPACE] == true))
				{

					pos_y -= grawitacja;
					grawitacja -= 1;
					skok = true;
					czy_bohater_wzlatuje = true;

					
					if (grawitacja <= 0)
					{
						czy_bohater_spada = true;
						czy_bohater_wzlatuje = false;
					}


					if (grawitacja == -16)
					{
						keys[SPACE] = false;
						grawitacja = 15;
						skok = false;
					}
				}





//=================================================//

			
				//KOLIDERY GRUNTU(grawitacja dziala jesli to cos NIE JEST) //795x182
				i = 0;
			
				while ((i < 20) && (dotyka_gruntu != true))
				{
					if (!(((kolider_x + 41 > 0) && (kolider_x + 41 < 795) && (pos_y + i > 825) && (pos_y < 1007))
						|| ((kolider_x + 41 > 850) && (kolider_x + 41 < 1645) && (pos_y + i > 825) && (pos_y < 1007))
						|| ((kolider_x + 41 > 1645) && (kolider_x + 41 < 2440) && (pos_y + i > 825 + 50) && (pos_y < 1007+ 50))
						|| ((kolider_x + 41 > 2440) && (kolider_x + 41 < 3235) && (pos_y + i > 825) && (pos_y < 1007))
						|| ((kolider_x + 41 > 3235) && (kolider_x + 41 < 4030) && (pos_y + i > (825 - 45)) && (pos_y < (1007 - 45)))
						|| ((kolider_x + 41 > 4130) && (kolider_x + 41 < 4925) && (pos_y + i > (825 + 45)) && (pos_y < (1007 + 45)))
						|| (skok == true)))
					{
						dotyka_gruntu = false;
					}
					else
					{
						dotyka_gruntu = true;//sa wazne dla spa
					
						if (czy_skonczyc_skok == true)
						{
							keys[SPACE] = false;
							czy_bohater_spada = false;
							czy_bohater_wzlatuje = false;
							grawitacja = 15;
							skok = false;
						}
					}
					i++;
				}


			

				if ((dotyka_gruntu == false) && (skok != true))
				{
					pos_y = pos_y + 20;
					czy_bohater_spada = true;

				}
				if((dotyka_gruntu == true)&& (skok!=true))
				{
					pos_y = pos_y - (20-i);
					czy_bohater_spada = false;
					czy_bohater_wzlatuje = false;

				}
			

				i = 0;
				dotyka_gruntu = false;
				czy_skonczyc_skok = false;


//=======================================================================================================================================//
								//PAN ZEGAREK


				zegarek++;
				if (zegarek == 120)
				{
					zegarek = 0;
				}

				zegarek_animacja_boh++;
				if (zegarek_animacja_boh == 50)
				{
					zegarek_animacja_boh = 0;
				}

				if (czy_bohater_atakuje == true)
				{
					zegarek_atak++;
				}

				if (zegarek_atak == 60)
				{
					zegarek_atak = 0;
					keys[P] = false;
					czy_bohater_atakuje = false;
				}

				if (czas_po_utracie_zycia != 0)
				{
					czas_po_utracie_zycia -= 1;
				}

				if (czas_po_utracie_zycia_wroga != 0)
				{
					czas_po_utracie_zycia_wroga -= 1;
				}

				if (czy_strzala_leci == true)
				{
					zegarek_strzala++;
					if (zegarek_strzala == 21)
					{
						if (strzala_g < 21)
						{
							strzala_g++;
						}
						zegarek_strzala = 0;
					}
				}


//=================================================//
				//KOLIDERY PRZECIWNIKÓW


				if ((((kolider_x > grunt1_x + 1000 + kolider_w1) && (kolider_x < grunt1_x + 1000 + kolider_w1 + 220)&&(czy_wrog1_martwy!=true)) 
					|| ((kolider_x > grunt1_x + 1300 + kolider_w2) && (kolider_x < grunt1_x + 1300 + kolider_w2 + 220) && (czy_wrog2_martwy != true)))
					&& (czas_po_utracie_zycia == 0)&&(czy_bohater_atakuje==false))
				{
					ilosc_zyc -= 1;
					czas_po_utracie_zycia = 60;
				}

				if ((((kolider_x > grunt1_x + 1000 + kolider_w1) && (kolider_x < grunt1_x + 1000 + kolider_w1 + 220))
					&&(czas_po_utracie_zycia_wroga == 0) && (czy_bohater_atakuje==true)))
				{
					zycie_w1--;
					czas_po_utracie_zycia_wroga = 35;
				}
				if ((((kolider_x > grunt1_x + 1300 + kolider_w2) && (kolider_x < grunt1_x + 1300 + kolider_w2 + 220)))
					&& (czas_po_utracie_zycia_wroga == 0) && (czy_bohater_atakuje==true))
				{
					zycie_w2--;
					czas_po_utracie_zycia_wroga = 35;
				}
				 

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//ZACHOWANIE STRZALY

				kat_strzalu = tan((mysz_y-(float)pos_y) / (mysz_x-(float)pos_x));

				if (czy_strzala_leci==true)
				{
					if ((strzal_prawo == true)&&(naciag_x>0))
					{
						strzala_x = strzala_x + (12*(naciag_x/400));
					}

					if ((strzal_lewo == true) && (naciag_x<0))
					{
						strzala_x = strzala_x + (12 * (naciag_x / 400));
					}
					
					strzala_y = strzala_y + strzala_g;
				}



				przerys = true;//ROBI ZA WZNOWIENIE CZASU
			}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//KOLEJKOWANIE WYDARZEÑ/WYŒWIETLANIA


			if (przerys && al_is_event_queue_empty(event_queue))//unika ghostow
			{
				przerys = false;


				al_draw_bitmap(tlo_gl, 0 + kamera_x / 3, 0, 0);
				al_draw_bitmap(tlo2, (0 + kamera_x * 2) / 3, 0, 0);

				if (ilosc_zyc == 3)
				{
					al_draw_bitmap(zycie, 30 + 138, 10, 0);
				}


				if (ilosc_zyc >= 2)
				{
					al_draw_bitmap(zycie, 20 + 69, 10, 0);
				}


				if (ilosc_zyc >= 1)
				{
					al_draw_bitmap(zycie, 10, 10, 0);
				}

				al_draw_circle(pos_x, pos_y, 400, al_map_rgb(255, 0, 0), 3);

			
														//Animacje bohatera


				if (ostatni_ruch == 0)
				{
					if (((keys[A] == true) && (keys[D] == true)) && (skok != true))
					{
						al_draw_bitmap(bohater, pos_x, pos_y + 15, ALLEGRO_FLIP_HORIZONTAL);
						ruchAD = true;
					}
					if (((zegarek_animacja_boh >= 0) && (zegarek_animacja_boh < 25) && (czy_bohater_biegnie == true) && (czy_bohater_spada != true) && (czy_bohater_wzlatuje != true) && (czy_bohater_atakuje != true)) && (ruchAD == false))
					{
						al_draw_bitmap(ruch_boh1, pos_x, pos_y + 15, 0);
					}
					if (((zegarek_animacja_boh >= 25) && (zegarek_animacja_boh < 50) && (czy_bohater_biegnie == true) && (czy_bohater_spada != true) && (czy_bohater_wzlatuje != true) && (czy_bohater_atakuje != true)) && (ruchAD == false))
					{
						al_draw_bitmap(ruch_boh2, pos_x, pos_y + 15, 0);
					}

					ruchAD = false;

					if ((czy_bohater_biegnie == false) && (czy_bohater_spada != true) && (czy_bohater_wzlatuje != true) && (czy_bohater_atakuje != true)&&(czy_bohater_naciaga==false))
					{
						al_draw_bitmap(bohater, pos_x, pos_y + 15, 0);
					}
					if ((czy_bohater_wzlatuje == true) && (czy_bohater_atakuje != true))
					{
						al_draw_bitmap(skok_gora, pos_x, pos_y + 15, 0);
					}
					if ((czy_bohater_spada == true) && (czy_bohater_atakuje != true))
					{
						al_draw_bitmap(skok_dol, pos_x, pos_y + 15, 0);
					}
					if (czy_bohater_atakuje == true)
					{
						al_draw_bitmap(atak, pos_x, pos_y + 15, 0);
					}
					if ((czy_bohater_biegnie == false) && (czy_bohater_spada != true) && (czy_bohater_wzlatuje != true) && (czy_bohater_atakuje != true) && (czy_bohater_naciaga == true))
					{
						al_draw_bitmap(naciag, pos_x, pos_y + 15, 0);
					}
				}
				else
				{
					if (((keys[A] == true) && (keys[D] == true))&&(skok!=true))
					{
						al_draw_bitmap(bohater, pos_x, pos_y + 15, 0);
						ruchAD = true;
					}
					if (((zegarek_animacja_boh >= 0) && (zegarek_animacja_boh < 25) && (czy_bohater_biegnie == true) && (czy_bohater_spada != true) && (czy_bohater_wzlatuje != true)&&(czy_bohater_atakuje!=true)) && (ruchAD == false))
					{
						al_draw_bitmap(ruch_boh1, pos_x, pos_y + 15, ALLEGRO_FLIP_HORIZONTAL);
					}
					if (((zegarek_animacja_boh >= 25) && (zegarek_animacja_boh < 50) && (czy_bohater_biegnie == true) && (czy_bohater_spada != true) && (czy_bohater_wzlatuje != true) && (czy_bohater_atakuje != true)) && (ruchAD==false))
					{
						al_draw_bitmap(ruch_boh2, pos_x, pos_y + 15, ALLEGRO_FLIP_HORIZONTAL);
					}

					ruchAD = false;

					if((czy_bohater_biegnie==false) && (czy_bohater_spada != true) && (czy_bohater_wzlatuje != true) && (czy_bohater_atakuje != true) && (czy_bohater_naciaga==false))
					{
						al_draw_bitmap(bohater, pos_x, pos_y + 15, ALLEGRO_FLIP_HORIZONTAL);
					}
					if ((czy_bohater_wzlatuje == true) && (czy_bohater_atakuje != true))
					{
						al_draw_bitmap(skok_gora, pos_x, pos_y + 15, ALLEGRO_FLIP_HORIZONTAL);
					}
					if ((czy_bohater_spada == true) && (czy_bohater_atakuje != true))
					{
						al_draw_bitmap(skok_dol, pos_x, pos_y + 15, ALLEGRO_FLIP_HORIZONTAL);
					}
					if (czy_bohater_atakuje == true)
					{
						al_draw_bitmap(atak, pos_x, pos_y + 15, ALLEGRO_FLIP_HORIZONTAL);
					}
					if ((czy_bohater_biegnie == false) && (czy_bohater_spada != true) && (czy_bohater_wzlatuje != true) && (czy_bohater_atakuje != true) && (czy_bohater_naciaga == true))
					{
						al_draw_bitmap(naciag, pos_x, pos_y + 15, ALLEGRO_FLIP_HORIZONTAL);
					}
				}

				//WYSWIETLANIE ELEMENTOW
				//al_draw_bitmap(strzala, mysz_x, mysz_y, 0);

				al_draw_bitmap(strzala, strzala_x, strzala_y, 0);


													//WYSWIETLANIE GRUNTU
				al_draw_bitmap(grunt1, grunt1_x + kamera_x, grunt1_y, 0);
				al_draw_bitmap(grunt1, grunt1_x + 850 + kamera_x, grunt1_y, 0);
				al_draw_bitmap(grunt1, grunt1_x + 1645 + kamera_x, grunt1_y + 50, 0);
				al_draw_bitmap(grunt1, grunt1_x + 2440 + kamera_x, grunt1_y, 0);
				al_draw_bitmap(grunt1, grunt1_x + 3235 + kamera_x, grunt1_y-45, 0);

				al_draw_bitmap(grunt1, grunt1_x + 4130 + kamera_x, grunt1_y + 45, 0);

		



													//PRZECIWNICY
				if (zycie_w1 > 0)
				{
					al_draw_bitmap(wrog1, grunt1_x + 1000 + kamera_x + kolider_w1, grunt1_y - 80, 0);
				}
				else
				{
					czy_wrog1_martwy = true;
				}
				if (zycie_w2 > 0)
				{
					al_draw_bitmap(wrog2, grunt1_x + 1300 + kamera_x + kolider_w2, grunt1_y - 80, 0);
				}
				else
				{
					czy_wrog2_martwy = true;
				}


													//ZYCIE PRZECIWNIKOW
				if (zycie_w1 >= 2)
				{
					al_draw_bitmap(zycie_zielone, grunt1_x + 1000 + kamera_x + kolider_w1 + 40, grunt1_y - 120, 0);
				}
				if (zycie_w1 >= 1)
				{
					al_draw_bitmap(zycie_zielone, grunt1_x + 1000 + kamera_x + kolider_w1 - 40, grunt1_y - 120, 0);
				}
				if (zycie_w2 >= 2)
				{
					al_draw_bitmap(zycie_zielone, grunt1_x + 1300 + kamera_x + kolider_w2 + 40, grunt1_y - 120, 0);
				}
				if (zycie_w2 >= 1)
				{
					al_draw_bitmap(zycie_zielone, grunt1_x + 1300 + kamera_x + kolider_w2 - 40, grunt1_y - 120, 0);
				}

				al_draw_textf(font18, al_map_rgb(50, 0, 255), 350, 50, ALLEGRO_ALIGN_LEFT, "Mysz x: %f", mysz_x);
				al_draw_textf(font18, al_map_rgb(50, 0, 255), 350, 150, ALLEGRO_ALIGN_LEFT, "Mysz y %f", mysz_y);
				al_draw_textf(font18, al_map_rgb(50, 0, 255), 350, 250, ALLEGRO_ALIGN_LEFT, "kat strzaly: %f", kat_strzalu);

				al_draw_textf(font18, al_map_rgb(200, 0, 255), 150, 150, ALLEGRO_ALIGN_LEFT, "Naciag x to: %i", naciag_x);
				al_draw_textf(font18, al_map_rgb(255, 0, 0), 1700, 50, 0, "Kolider x to: %i", kolider_x);








//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//WYŒWIETLANIE


				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}

	
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//EKRAN SMIERCI I RESET WARTOSCI
			ALLEGRO_EVENT smierc1;
			al_wait_for_event(event_queue, &smierc1);

			if (smierc1.type == ALLEGRO_EVENT_KEY_UP)//esc wylacza okno
			{
				switch (smierc1.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					smierc = true;
					break;
				case ALLEGRO_KEY_SPACE:
					done = false;
					pos_x = 10;
					pos_y = (wysokosc * 3) / 4;
					kamera_x = 0;
					ilosc_zyc = 3;
					keys[D] = false;
					keys[A] = false;
					ostatni_ruch = 0;
					ilosc_zyc = 3;
					zycie_w1 = 2;
					zycie_w2 = 2;
					czy_wrog1_martwy = false;
					czy_wrog2_martwy = false;
					break;
				}
			}


				al_draw_bitmap(smierc2, 0, 0, 0);
			

			

			al_flip_display();
		}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//CZYSZCZENIE

		al_destroy_display(okno);
		al_destroy_bitmap(bohater);
		al_destroy_bitmap(grunt1);
		al_destroy_bitmap(wrog1);
		al_destroy_bitmap(wrog2);
		al_destroy_bitmap(tlo2);
		al_destroy_bitmap(tlo_gl);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);

	return 0;
}