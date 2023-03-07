#include "Library.h"

std::string MettreMajuscule(std::string s) //Fonction pour mettre les caractere d'une string en majuscule,
{                                          // methode tiré du site : https://www.delftstack.com/fr/howto/cpp/how-to-convert-string-to-uppercase-cpp
                                           // methode utile pour afficher en gros les noms de pistes et sommets
    std::transform(s.begin(), s.end(), s.begin(),[](unsigned char c){ return toupper(c); });
    return s;
}

int main()
{
    // init allegro
    allegro_init();

    // install allegro's routines
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT, DIGI_AUTODETECT, NULL);

    set_color_depth(desktop_color_depth());

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("problem color");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // init color settings
    set_alpha_blender();
    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);


    // window name
    set_window_title("____________________________________________________________________ STATION LES ARCS ________________________________________________________");

    //Affichage en tout temps de la sourie sur l'ecran
    show_mouse(screen);

    //Initialisation aleatoire
    srand(time(NULL));

    //Declaration structure images
    Images Ima ;
    //Declaration structure musics
    samples Samp;

    //Declaration et initialisation des parametre de la music
    sound Musi;
    Musi.volume = 255;
    Musi.music_on = true;

    //Initialisation graphe
    Graphe grapho ("StationSki.txt",false);


     //Chargement images
    LoadImages(&Ima);

    //Chargement musiques
    InitSamples(&Samp);


    //Partie activation de la borne par son ecran d'acceuille
    EcranAcceuilleBorne(Ima,Samp,&Musi,grapho);

    EraseImages(&Ima);

    EraseSample(&Samp);

    std::cout << "Au revoir" << std::endl;

    return 0;
}
END_OF_MAIN();
