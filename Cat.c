//Apertar "S" para começar o jogo
// (No menu)--> "r" highscore, "esc" sai do jogo, "s" começa novo jogo
// "p" pausa --(na pausa)--> "esc" volta para o menu, "r" recomeça o jogo do 0, "p" volta ao jogo

//Mudança de tiro para vetor de struct  --- v0.2.0!
//Inimigo e troca de frame ao andar <tiro de 10 em 10 frames>  --- v0.2.2!
//Criar fases, inimigos nascendo e morrendo em cada fase, player morrendo, implementar o menu e pausa e (sprites) --- v0.3!!!!
///////////// METAS --> CHEFÂO, RECORD, 3 FASES, BONUS NO MAPA, INDICADOR DE VIDA,
///////////// SPRITE DE MORTE

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define MAX_BULLETCOUNT 50
#define MAX_ENEMY 100

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int k;
int ene_posi[MAX_ENEMY];
int vivendo=5;
int muda[MAX_ENEMY];

int gameRunning = 1;
int menuRunning = 1;
int andar_inimigo=0;
int and_boss=0;
int inimigos_da_fase;
int max_inimigos;
int menu=0;
int pontuacao=0;
int BULLET_FRAME_HW=6;
int cont_morte = 100;

// TFF
char s_pontos[10];
char level[10];
char pontos[100];
SDL_Surface* escrever_pontos = NULL;
SDL_Surface* escrever_level = NULL;
SDL_Surface* escrever_palavra = NULL;
TTF_Font *fonte;
TTF_Font *fonte_2;
SDL_Color cor = {0, 255, 0};
SDL_Color cor_2 = {255, 255, 255};

SDL_Rect fonte_posi, pontos_posi, level_posi;


//


int coli_si_width = 352;

Mix_Music *MusicaJogo = NULL;

//estrutura do tiro
typedef struct _BULLET
{
    int posi;
    int tiro;
}BULLET;
//

    //////////////////////////////////////////////////////////////
    //                                                          //
    //                         Funções                          //
    //                                                          //
    //////////////////////////////////////////////////////////////

    //
    void boss_up(int boss_alive, SDL_Surface* tela, SDL_Surface* boss, SDL_Rect coli_superior_di_posi, SDL_Rect coli_superior_es_posi, SDL_Rect coli_inferior_di_posi, SDL_Rect coli_inferior_es_posi, SDL_Rect coli_direita_sup_posi, SDL_Rect coli_direita_inf_posi, SDL_Rect coli_esquerda_sup_posi, SDL_Rect coli_esquerda_inf_posi, float velboss, SDL_Rect boss_position, SDL_Rect boss_frame, SDL_Rect player_position, int BOSS_FRAME_WIDTH, int BOSS_FRAME_HEIGHT);
    void atirador(int gun, int *enemy_alive, int enemy_frame_width, int enemy_frame_height, SDL_Rect enemy_position[], BULLET bullet_vet[], float velobull, SDL_Surface* bullet, SDL_Rect bullet_frame, SDL_Rect bullet_position[], SDL_Surface* tela);
    void update_enemies(SDL_Rect coli_superior_di_posi, SDL_Rect coli_superior_es_posi, SDL_Rect coli_inferior_di_posi, SDL_Rect coli_inferior_es_posi, SDL_Rect coli_direita_sup_posi, SDL_Rect coli_direita_inf_posi, SDL_Rect coli_esquerda_sup_posi, SDL_Rect coli_esquerda_inf_posi,
        BULLET bullet_vet[], int *enemy_alive, SDL_Rect enemy_position[], SDL_Rect player_position, float vele, SDL_Surface* enemy, SDL_Rect enemy_frame[], SDL_Surface* tela, int enemy_frame_width, int enemy_frame_height, SDL_Rect bullet_position[]);

    void create_enemy(SDL_Rect enemy_position[], int *enemy_alive);

    void zerar(int *enemy_alive)
    {
        int i;
        for(i=0; i<MAX_ENEMY; i++)
        {
            enemy_alive[i]=0;
        }
    }
    //

int main( int argc, char* args[] )
{
    ////////////////////////////////////////////////////////////
    //                                                        //
    //                      Variáveis                         //
    //                                                        //
    ////////////////////////////////////////////////////////////

    //

    float velx = 4.5;
    float vele = 3.5;
    float velobull = 7.5;
    float velboss = 3.0;
    //
    for(k=0; k<MAX_ENEMY; k++)
        muda[k] = 10;
    int pausa=0, pausado=0, despausado = 4, outmenu=1, score=0;
    int game=1;
    int fase = 1;
    int i=0, andar=1;
    int bullet_cont=10;
    int item, posi1_item, posi2_item;

    int player_fullwidth = 424;
    int player_frame_width = 39;
    int player_frame_height = 50;
    int enemy_frame_width = 51;
    int enemy_frame_height = 50;
    int BOSS_FRAME_WIDTH = 100;
    int BOSS_FRAME_HEIGHT = 114;
    int ITEM_FRAME_HW = 24; 
    
    int cont_enemy;
    int cont_frame_bullet;
    int horda;
    int cont_surgir = 300;
    int tempo_arma = 0;

    int enemy_alive[MAX_ENEMY];
    int n_vidas=4;
    int vid;
    int gun = 10;
    int boss_alive=0;

    

    //
    BULLET bullet_vet[MAX_BULLETCOUNT];


    //Variaveis da Tela

    //
    SDL_Window* window = NULL;

    SDL_Surface* rabhix = NULL;
    SDL_Surface* barra_de_vidas = NULL;
    SDL_Surface* tela = NULL;
    SDL_Surface* menupausa = NULL;
    SDL_Surface* fundo = NULL;
    SDL_Surface* fundo_terra = NULL;
    SDL_Surface* player = NULL;
    SDL_Surface* bullet = NULL;
    SDL_Surface* menuBackGround = NULL;
    SDL_Surface* Start = NULL;
    SDL_Surface* enemy = NULL;
    SDL_Surface* boss = NULL;
    SDL_Surface* gameover = NULL;
    SDL_Surface* itens = NULL;

    

    SDL_Surface* Intro = NULL;
    //
    SDL_Surface* coli_inferior_di = NULL;
    SDL_Surface* coli_inferior_es = NULL;
    SDL_Surface* coli_esquerda_sup = NULL;
    SDL_Surface* coli_esquerda_inf = NULL;
    SDL_Surface* coli_direita_sup = NULL;
    SDL_Surface* coli_direita_inf = NULL;
    SDL_Surface* coli_superior_di = NULL;
    SDL_Surface* coli_superior_es = NULL;
    //

    //Estado de de teclas pressionadas declarada em "keystate"
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    //
    //

    ///////////////////////////////////////////////////////////
    //                                                       //
    //                          Rects                        //
    //                                                       //
    ///////////////////////////////////////////////////////////
    
    //

    //Rects itens
    SDL_Rect item_posi, item_frame;

    item_posi.x = 0;
    item_posi.y = 0;
    item_posi.w = ITEM_FRAME_HW;
    item_posi.h = ITEM_FRAME_HW;

    item_frame.x = 0;
    item_frame.y = 0;
    item_frame.w = ITEM_FRAME_HW;
    item_frame.h = ITEM_FRAME_HW;
    //

    //Rect corações

    SDL_Rect core_position, core_frame;

    core_position.x = 630;
    core_position.y = 38;
    core_position.w = 116;
    core_position.h = 22;

    core_frame.x = 630;
    core_frame.y = 38;
    core_frame.w = 116;
    core_frame.h = 22;
    //

    //Rect introdução
    SDL_Rect intro_frame, intro_position;

    intro_frame.x=0;
    intro_frame.y=0;
    intro_frame.w=SCREEN_WIDTH;
    intro_frame.h=SCREEN_HEIGHT;

    intro_position.x=0;
    intro_position.y=0;
    intro_position.w=SCREEN_WIDTH;
    intro_position.h=SCREEN_HEIGHT;
    //

    //Rects menu pausa
    SDL_Rect pausa_position;

    pausa_position.x = (SCREEN_WIDTH/2)-(600/2);
    pausa_position.y = (SCREEN_HEIGHT/2)-(450/2);
    pausa_position.w = 600;
    pausa_position.h = 450;
    //

    //Rects de personagens
    SDL_Rect player_frame, player_position;
    
    player_frame.x = 0;
    player_frame.y = 0;
    player_frame.w = player_frame_width;
    player_frame.h = player_frame_height;

    player_position.x = SCREEN_WIDTH/2;
    player_position.y = SCREEN_HEIGHT/2;
    player_position.w = player_frame_width;
    player_position.h = player_frame_height;
    //

    //Rect boss
    SDL_Rect boss_position, boss_frame;

    boss_position.x = 0;
    boss_position.y = 0;
    boss_position.w = BOSS_FRAME_WIDTH;
    boss_position.h = BOSS_FRAME_HEIGHT;

    boss_frame.x = 0;
    boss_frame.y = 0;
    boss_frame.w = BOSS_FRAME_WIDTH;
    boss_frame.h = BOSS_FRAME_HEIGHT;
    //

    //Rect letras, pontuacao
    fonte_posi.x = 50;
    fonte_posi.y = 40;
    fonte_posi.w = 0;
    fonte_posi.h = 0;

    pontos_posi.x = 50;
    pontos_posi.y = 60;
    pontos_posi.w = 0;
    pontos_posi.h = 0;

    level_posi.x = (SCREEN_WIDTH/2)-30;
    level_posi.y = (SCREEN_HEIGHT/2)-30;
    level_posi.w = 0;
    level_posi.h = 0;

    //

    //Rect para os inimigos

    SDL_Rect enemy_frame[MAX_ENEMY], enemy_position[MAX_ENEMY];

    for(cont_enemy=0; cont_enemy<MAX_ENEMY; cont_enemy++)
    {
        enemy_frame[cont_enemy].x = 0;
        enemy_frame[cont_enemy].y = 0;
        enemy_frame[cont_enemy].w = enemy_frame_width;
        enemy_frame[cont_enemy].h = enemy_frame_height;

        enemy_position[cont_enemy].x = 0;
        enemy_position[cont_enemy].y = 0;
        enemy_position[cont_enemy].w = enemy_frame_width;
        enemy_position[cont_enemy].h = enemy_frame_height;
    }
    //

    //Rect para o tiro

    SDL_Rect bullet_frame, bullet_position[MAX_BULLETCOUNT];

    bullet_frame.x = 0;
    bullet_frame.y = 0;
    bullet_frame.w = 6;
    bullet_frame.h = 6;

    for(cont_frame_bullet=0; cont_frame_bullet<MAX_BULLETCOUNT; cont_frame_bullet++)
    {
        
        bullet_position[cont_frame_bullet].x = 811;
        bullet_position[cont_frame_bullet].y = 0;
        bullet_position[cont_frame_bullet].w = 6;
        bullet_position[cont_frame_bullet].h = 6;
    }
    //

    //Rect para colisao da parede
    SDL_Rect coli_superior_es_posi, coli_superior_di_posi, coli_inferior_di_posi, coli_inferior_es_posi, coli_direita_sup_posi,
    coli_direita_inf_posi, coli_esquerda_sup_posi, coli_esquerda_inf_posi;

    coli_superior_es_posi.x = 0;
    coli_superior_es_posi.y = 0;
    coli_superior_es_posi.w = coli_si_width;
    coli_superior_es_posi.h = 71;

    coli_superior_di_posi.x = 352+96;
    coli_superior_di_posi.y = 0;
    coli_superior_di_posi.w = coli_si_width;
    coli_superior_di_posi.h = 71;

    coli_inferior_es_posi.x = 0;
    coli_inferior_es_posi.y = 568;
    coli_inferior_es_posi.w = coli_si_width;
    coli_inferior_es_posi.h = 32;

    coli_inferior_di_posi.x = 352+96;
    coli_inferior_di_posi.y = 568;
    coli_inferior_di_posi.w = coli_si_width;
    coli_inferior_di_posi.h = 32;

    coli_esquerda_sup_posi.x = 0;
    coli_esquerda_sup_posi.y = 0;
    coli_esquerda_sup_posi.w = 62;
    coli_esquerda_sup_posi.h = 273;

    coli_esquerda_inf_posi.x = 0;
    coli_esquerda_inf_posi.y = 273+95;
    coli_esquerda_inf_posi.w = 62;
    coli_esquerda_inf_posi.h = 232;

    coli_direita_sup_posi.x = 738;
    coli_direita_sup_posi.y = 0;
    coli_direita_sup_posi.w = 62;
    coli_direita_sup_posi.h = 273;

    coli_direita_inf_posi.x = 738;
    coli_direita_inf_posi.y = 273+95;
    coli_direita_inf_posi.w = 62;
    coli_direita_inf_posi.h = 232;
    //


    /////////////////////////////////////////////////////////////////////////////////////
    //                                                                                 //
    //                              Imagens a serem carregadas                         //
    //                                                                                 //
    //                                                                                 //
    /////////////////////////////////////////////////////////////////////////////////////
    //
    rabhix = IMG_Load("rabhix_vid.png");
    Start = IMG_Load("START.png");
    barra_de_vidas = IMG_Load("core.png");
    menuBackGround = IMG_Load("background.jpg");
    menupausa = IMG_Load("menupausa.png");
    enemy = IMG_Load("inimigo.png");
    boss = IMG_Load("pomba.png");
    bullet = IMG_Load("bullet.png");
    player = IMG_Load("Cat.png");
    gameover = IMG_Load("gameover.png");
    itens = IMG_Load("itens.png");

    Intro = IMG_Load("intro.jpg");


    fundo_terra = IMG_Load("fundo_terra.png");
    fundo = IMG_Load("fundo_cima.png");

    //Imagens colisao
    coli_inferior_di = IMG_Load("coli_inferior_di.png");
    coli_inferior_es = IMG_Load("coli_inferior_es.png");
    coli_esquerda_sup = IMG_Load("coli_esquerda_sup.png");
    coli_esquerda_inf = IMG_Load("coli_esquerda_inf.png");
    coli_direita_sup = IMG_Load("coli_direita_sup.png");
    coli_direita_inf = IMG_Load("coli_direita_inf.png");
    coli_superior_di = IMG_Load("coli_superior_di.png");
    coli_superior_es = IMG_Load("coli_superior_es.png");
    //
    //

    zerar(enemy_alive);
    //Initialize SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)<0)
    {
        printf("SDL_mixer não pode inicializar: %s\n", Mix_GetError());
        return 0;
    }
    MusicaJogo = Mix_LoadMUS("song2.mp3");

    if (TTF_Init()==-1)
    {
        printf("ERRO NO TTF\n");
        exit(0);
    }

    //inicia o ttf
    TTF_Init();
    fonte = TTF_OpenFont("Fixedsys500c.ttf",18);
    fonte_2 = TTF_OpenFont("Fixedsys500c.ttf",60);

    //Create window
    window = SDL_CreateWindow( "Cat Bio Defender v0.3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    //Get window surface
    tela = SDL_GetWindowSurface(window);


    //Cria o evento "teclar"
    SDL_Event teclar;
    
    keystate = SDL_GetKeyboardState(NULL);

    for(vid=0; vid*SCREEN_WIDTH<5600; vid++)
    {
        intro_frame.x = vid*SCREEN_WIDTH;
        SDL_BlitSurface(rabhix ,&intro_frame, tela, &intro_position);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(300);
    }
    for(vid=0; vid*SCREEN_WIDTH<5600; vid++)
    {
        intro_frame.x = vid*SCREEN_WIDTH;
        SDL_BlitSurface(Intro ,&intro_frame, tela, &intro_position);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(700);
    }

    SDL_FreeSurface(Intro);
    SDL_FreeSurface(rabhix);
    

    while(gameRunning)
    {
        while(menuRunning)
        {
            

            SDL_BlitSurface(menuBackGround, NULL, tela, NULL);
            SDL_BlitSurface(Start, NULL, tela, NULL);

            if(menu == 0)
            {
                if(keystate[SDL_SCANCODE_S])
                {
                    menuRunning = 0;
                    game =1;
                    outmenu =0;
                    menu=10;
                    fase=1;
                }
                if(keystate[SDL_SCANCODE_R])
                {
                    score = 1;
                }
                if(keystate[SDL_SCANCODE_ESCAPE])
                {
                    pausa=0;
                    gameRunning=0;
                    menuRunning=0;
                    SDL_FreeSurface(menuBackGround);
                    SDL_FreeSurface(menupausa);
                    SDL_FreeSurface(Start);
                    SDL_FreeSurface(fundo);
                    SDL_FreeSurface(fundo_terra);
                    SDL_FreeSurface(player);
                    SDL_FreeSurface(bullet);
                    SDL_FreeSurface(gameover);
                    SDL_FreeSurface(boss);

                }
            }
            

            if(SDL_PollEvent(&teclar))
            {
                   
                if(teclar.type == SDL_QUIT)
                {
                    menuRunning = 0;
                    gameRunning = 0;
                }
            }

            if(menu>0)
                    menu--;
            SDL_UpdateWindowSurface(window);
            SDL_Delay(30);
        }
        while(pausa)
        {
            Mix_PauseMusic();
            if(pausado == 5)
            {
                if(keystate[SDL_SCANCODE_P])
                {
                    pausa = 0;
                    pausado=0;
                    despausado = 0;
                }
                if(keystate[SDL_SCANCODE_ESCAPE])
                {
                    outmenu = 1;
                    pausa = 0;
                    menuRunning=1;
                }
            }
            if(keystate[SDL_SCANCODE_Q])
            {
                game=1;
                pausa=0;
                fase=1;
            }
            if(SDL_PollEvent(&teclar))
            { 
                if(teclar.type == SDL_QUIT)
                {
                    menuRunning = 0;
                    gameRunning = 0;
                }
                
            }
            if(pausado < 5)
                pausado++;

            SDL_BlitSurface(menupausa, NULL, tela, &pausa_position);
            SDL_UpdateWindowSurface(window);
            SDL_Delay(20);
        }
        Mix_ResumeMusic();

        if(game == 1)
        {
            sprintf(level, "%d", fase);
            escrever_level = TTF_RenderText_Solid(fonte_2, level, cor_2);

            cont_morte = 100;
            
            Mix_PlayMusic(MusicaJogo, 1);

            boss_position.x = 0;
            boss_position.y = 0;
            boss_position.w = BOSS_FRAME_WIDTH;
            boss_position.h = BOSS_FRAME_HEIGHT;

            boss_frame.x = 0;
            boss_frame.y = 0;
            boss_frame.w = BOSS_FRAME_WIDTH;
            boss_frame.h = BOSS_FRAME_HEIGHT;

            if(fase == 1)
            {
                pontuacao = 0;
                n_vidas=4;

                core_position.x = 630;
                core_position.y = 38;
                core_position.w = 116;
                core_position.h = 22;

                core_frame.x = 0;
                core_frame.y = 0;
                core_frame.w = 116;
                core_frame.h = 22;
            }

            if(fase%4 == 0)
            {
                boss_alive =1;
                boss_position.x = SCREEN_WIDTH/2;
                boss_position.y = coli_superior_es_posi.h; 
            }

            max_inimigos = (fase*8)-2;
            inimigos_da_fase = max_inimigos;


            player_frame.x = 0;
            player_frame.y = 0;
            player_frame.w = player_frame_width;
            player_frame.h = player_frame_height;

            //Nosso rect para representar a posição do player na tela
            player_position.x = SCREEN_WIDTH/2;
            player_position.y = SCREEN_HEIGHT/2;
            player_position.w = player_frame_width;
            player_position.h = player_frame_height;

            //Rect para os inimigos
            zerar(enemy_alive);

            for(cont_enemy=0; cont_enemy<MAX_ENEMY; cont_enemy++)
            {
                enemy_frame[cont_enemy].x = 0;
                enemy_frame[cont_enemy].y = 0;
                enemy_frame[cont_enemy].w = 49;
                enemy_frame[cont_enemy].h = 50;

                enemy_position[cont_enemy].x = 811;
                enemy_position[cont_enemy].y = 0;
                enemy_position[cont_enemy].w = 49;
                enemy_position[cont_enemy].h = 50;
            }

            bullet_frame.x = 0;
            bullet_frame.y = 0;
            bullet_frame.w = 6;
            bullet_frame.h = 6;

            for(cont_frame_bullet=0; cont_frame_bullet<MAX_BULLETCOUNT; cont_frame_bullet++)
            {
                
                bullet_position[cont_frame_bullet].x = 811;
                bullet_position[cont_frame_bullet].y = 0;
                bullet_position[cont_frame_bullet].w = 6;
                bullet_position[cont_frame_bullet].h = 6;
            }
            game = 0;
        }

        if(despausado==4)
        {
            if(keystate[SDL_SCANCODE_P])
            {
                pausa=1;
            }
        }

        if(SDL_PollEvent(&teclar))
        {

            if(teclar.type == SDL_QUIT)
            {
                gameRunning = 0;
            }
        }

        if(cont_surgir == 0)
        {
            item = rand()%4;

            posi1_item = rand()%(SCREEN_WIDTH-200);
            posi2_item = rand()%(SCREEN_HEIGHT-200);

            if(posi1_item<200)
                posi1_item + 200;
            if(posi2_item<200)
                posi2_item + 200;

            
            switch(item)
            {
            case 0: item_frame.x = 0;
                break;

            case 1: item_frame.x = ITEM_FRAME_HW;
                break;

            case 2: item_frame.x = 2*ITEM_FRAME_HW;
                break;

            case 3: item_frame.x = 3*ITEM_FRAME_HW;
                break;
            }

            item_posi.x = posi1_item;
            item_posi.y = posi2_item;
        }
        if(item_posi.x < player_position.x +player_frame_width && item_posi.x +ITEM_FRAME_HW > player_position.x
        && item_posi.y < player_position.y +player_frame_height && item_posi.y +ITEM_FRAME_HW > player_position.y)
        {
            tempo_arma=200;
            switch(item)
            {
            case 0: pontuacao += 300;
                break;

            case 1: gun = 4;
                    bullet_frame.x = BULLET_FRAME_HW;
                break;

            case 2: gun = 2;
                    bullet_frame.x = 2*BULLET_FRAME_HW;
                break;

            case 3: if(n_vidas < 4)
                    {
                        n_vidas++;
                        core_frame.x -=30;
                    }

                break;
            }

            item_posi.x = 0;
            item_posi.y = 0;     
        }
        if(cont_surgir == 100)
        {
            item_posi.x = 0;
            item_posi.y = 0;   
        }

        if(cont_morte == 100)
        {
            for(horda=0; horda<max_inimigos; horda++)
            {
                if(enemy_position[horda].x < player_position.x +player_frame_width && enemy_position[horda].x +enemy_frame_width > player_position.x
                && enemy_position[horda].y < player_position.y +player_frame_height && enemy_position[horda].y +enemy_frame_height > player_position.y)
                {
                    n_vidas--;
                    player_position.y = SCREEN_HEIGHT/2;
                    player_position.x = 0;
                    core_frame.x +=30;

                    cont_morte =0;
                }
            }
        }

        if(cont_morte<100)
        {
            vele = 0;
        }
        else
            vele = 3.5;

        if(n_vidas==0)
        {
            core_frame.x +=30;
            SDL_BlitSurface(gameover, NULL, tela, &pausa_position);
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
            SDL_FreeSurface(gameover);
            
            menuRunning=1;
        }


        //Teclas para movimento e tiro
        if (keystate[SDL_SCANCODE_UP] )
        {
            player_frame.y = 200;
            if(andar%2==0)
                player_frame.x = 39;
            else
                player_frame.x = 78;

            if(coli_esquerda_sup_posi.y+coli_esquerda_sup_posi.h < player_position.y
            || coli_direita_sup_posi.y+coli_direita_sup_posi.h < player_position.y 
            || coli_superior_es_posi.y+coli_superior_es_posi.h < player_position.y 
            || coli_superior_di_posi.y+coli_superior_di_posi.h < player_position.y
            || (coli_superior_di_posi.x > player_position.x + player_frame_width
            && coli_superior_es_posi.x+coli_inferior_es_posi.w < player_position.x))
                player_position.y -= velx;  
        }
        if (keystate[SDL_SCANCODE_LEFT] )
        {
            player_frame.y = 300;
            if(andar%2==0)
                player_frame.x = 39;
            else
                player_frame.x = 78;

            if(coli_esquerda_sup_posi.x+coli_esquerda_sup_posi.w < player_position.x
            || coli_esquerda_inf_posi.x+coli_esquerda_inf_posi.w < player_position.x 
            || coli_superior_es_posi.x+coli_superior_es_posi.w < player_position.x 
            || coli_inferior_es_posi.x+coli_inferior_es_posi.w < player_position.x
            || (coli_direita_sup_posi.y+coli_direita_sup_posi.h < player_position.y
                && coli_direita_inf_posi.y > player_position.y +player_frame_height))
                player_position.x -= velx;   
        }
        if (keystate[SDL_SCANCODE_DOWN] )
        {
            player_frame.y = 0;
            if(andar%2==0)
                player_frame.x = 39;
            else
                player_frame.x = 78;

            if(coli_esquerda_inf_posi.y > player_position.y +player_frame_height
            || coli_direita_inf_posi.y > player_position.y +player_frame_height 
            || coli_inferior_di_posi.y > player_position.y +player_frame_height
            || coli_inferior_es_posi.y > player_position.y +player_frame_height
            || (coli_inferior_di_posi.x > player_position.x + player_frame_width
            && coli_inferior_es_posi.x+coli_inferior_es_posi.w < player_position.x))
                player_position.y += velx;
        }
        if (keystate[SDL_SCANCODE_RIGHT] )
        {
            player_frame.y = 100;
            if(andar%2==0)
                player_frame.x = 39;
            else
                player_frame.x = 78;

            if(coli_direita_sup_posi.x > player_position.x + player_frame_width
            || coli_direita_inf_posi.x > player_position.x + player_frame_width 
            || coli_superior_di_posi.x > player_position.x + player_frame_width 
            || coli_inferior_di_posi.x > player_position.x + player_frame_width
            || (coli_direita_sup_posi.y+coli_direita_sup_posi.h < player_position.y
                && coli_direita_inf_posi.y > player_position.y +player_frame_height))
                player_position.x += velx;
        }
        if(keystate[SDL_SCANCODE_LEFT] && keystate[SDL_SCANCODE_UP])
        {
            player_frame.y=250;
            if(andar%2==0)
                player_frame.x = 39;
            else
                player_frame.x = 78;    
        }
        if(keystate[SDL_SCANCODE_LEFT] && keystate[SDL_SCANCODE_DOWN])
        {
            player_frame.y=350;
            if(andar%2==0)
                player_frame.x = 39;
            else
                player_frame.x = 78;    
        }
        if(keystate[SDL_SCANCODE_RIGHT] && keystate[SDL_SCANCODE_DOWN])
        {
            player_frame.y=50;
            if(andar%2==0)
                player_frame.x = 39;
            else
                player_frame.x = 78;    
        }
        if(keystate[SDL_SCANCODE_RIGHT] && keystate[SDL_SCANCODE_UP])
        {
            player_frame.y=150;
            if(andar%2==0)
                player_frame.x = 39;
            else
                player_frame.x = 78;
        }

        //tiro

        if(outmenu == 4)
        {
            if(keystate[SDL_SCANCODE_D] && keystate[SDL_SCANCODE_W])
            {
                if(bullet_cont==0)
                {
                    bullet_cont=gun;
                    i++;
                    if(i == MAX_BULLETCOUNT)
                        i=0;
                    bullet_position[i].x = player_position.x+player_frame_width;
                    bullet_position[i].y = player_position.y;
                        player_frame.y=150;
                        player_frame.x = 0;
                    bullet_vet[i].tiro = 1;
                    bullet_vet[i].posi=5;
                }
            }
            else if(keystate[SDL_SCANCODE_D] && keystate[SDL_SCANCODE_S])
            {
                if(bullet_cont==0)
                {
                    bullet_cont=gun;
                    i++;
                    if(i == MAX_BULLETCOUNT)
                    {
                        i=0;
                    }
                    bullet_position[i].x = player_position.x +player_frame_width;
                    bullet_position[i].y = player_position.y +player_frame_width;
                        player_frame.y=50;
                        player_frame.x = 0;
                    bullet_vet[i].tiro = 1;
                    bullet_vet[i].posi=6;
                }
            }
            else if(keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_W])
            {
                if(bullet_cont==0)
                {
                    bullet_cont=gun;
                    i++;
                    if(i == MAX_BULLETCOUNT)
                        i=0;
                    bullet_position[i].x = player_position.x;
                    bullet_position[i].y = player_position.y;
                        player_frame.y=250;
                        player_frame.x = 0;
                    bullet_vet[i].tiro = 1;
                    bullet_vet[i].posi=7;
                }
            }
            else if(keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_S])
            {
                if(bullet_cont==0)
                {
                    bullet_cont=gun;
                    i++;
                    if(i == MAX_BULLETCOUNT)
                        i=0;
                    bullet_position[i].x = player_position.x;
                    bullet_position[i].y = player_position.y +player_frame_width;
                        player_frame.y=350;
                        player_frame.x = 0;
                    bullet_vet[i].tiro = 1;
                    bullet_vet[i].posi=8;
                }
            }
            else if(keystate[SDL_SCANCODE_W])
            {
                if(bullet_cont==0)
                {
                    bullet_cont=gun;
                    i++;
                    if(i == MAX_BULLETCOUNT)
                        i=0;
                    bullet_position[i].x = player_position.x + (53/2);
                    bullet_position[i].y = player_position.y;
                        player_frame.y=200;
                        player_frame.x = 0;
                    bullet_vet[i].tiro = 1;
                    bullet_vet[i].posi=1;
                }
            }
            else if(keystate[SDL_SCANCODE_A])
            {
                if(bullet_cont==0)
                {
                    bullet_cont=gun;
                    i++;
                    if(i == MAX_BULLETCOUNT)
                        i=0;
                    bullet_position[i].x = player_position.x;
                    bullet_position[i].y = player_position.y + (53/2);
                        player_frame.y=300;
                        player_frame.x = 0;
                    bullet_vet[i].tiro = 1;
                    bullet_vet[i].posi=2;
                }
            }
            else if(keystate[SDL_SCANCODE_S])
            {
                if(bullet_cont==0)
                {
                    bullet_cont=gun;
                    i++;
                    if(i == MAX_BULLETCOUNT)
                        i=0;
                    bullet_position[i].x = player_position.x + (player_frame_width/3);
                    bullet_position[i].y = player_position.y + ((5*player_frame_height)/6);
                        player_frame.y=0;
                        player_frame.x = 0;
                    bullet_vet[i].tiro = 1;
                    bullet_vet[i].posi=3;
                }
            }
            else if(keystate[SDL_SCANCODE_D])
            {
                if(bullet_cont==0)
                {
                    bullet_cont=gun;
                    i++;
                    if(i == MAX_BULLETCOUNT)
                        i=0;
                    bullet_position[i].x = player_position.x+player_frame_width-6;
                    bullet_position[i].y = player_position.y + ((player_frame_height*3)/4);
                        player_frame.y=100;
                        player_frame.x = 0;
                    bullet_vet[i].tiro = 1;
                    bullet_vet[i].posi=4;
                }
            }
        }

        // Pontuação
        sprintf(pontos, "Pontos:");
        escrever_palavra = TTF_RenderText_Solid(fonte, pontos, cor);

        sprintf(s_pontos, "%d", pontuacao);
        escrever_pontos = TTF_RenderText_Solid(fonte, s_pontos, cor);
        //
        
        if(boss_alive == 0)
        {
            create_enemy(enemy_position, enemy_alive);
        }

        SDL_BlitSurface(fundo_terra, NULL, tela, NULL);
        update_enemies(coli_superior_di_posi, coli_superior_es_posi, coli_inferior_di_posi, coli_inferior_es_posi, coli_direita_sup_posi, coli_direita_inf_posi, coli_esquerda_sup_posi, coli_esquerda_inf_posi, bullet_vet, enemy_alive, enemy_position, player_position, vele, enemy, enemy_frame, tela, enemy_frame_width, enemy_frame_height, bullet_position);
        boss_up(boss_alive, tela, boss, coli_superior_di_posi, coli_superior_es_posi, coli_inferior_di_posi, coli_inferior_es_posi, coli_direita_sup_posi, coli_direita_inf_posi, coli_esquerda_sup_posi, coli_esquerda_inf_posi, velboss, boss_position, boss_frame, player_position, BOSS_FRAME_WIDTH, BOSS_FRAME_HEIGHT);
        atirador(gun, enemy_alive, enemy_frame_width, enemy_frame_height, enemy_position, bullet_vet, velobull, bullet, bullet_frame, bullet_position, tela);
        SDL_BlitSurface(player, &player_frame, tela, &player_position);
        
        SDL_BlitSurface(itens, &item_frame, tela, &item_posi);
        
        SDL_BlitSurface(fundo, NULL, tela, NULL);
        SDL_BlitSurface(escrever_palavra, NULL, tela, &fonte_posi);
        SDL_BlitSurface(escrever_pontos, NULL, tela, &pontos_posi);
        SDL_BlitSurface(escrever_level, NULL, tela, &level_posi); 


        SDL_BlitSurface(barra_de_vidas, &core_frame, tela, &core_position);
        //Update the surface
        SDL_UpdateWindowSurface(window);

        if(andar<=40)
            andar++;
        else
            andar=1;
        if(bullet_cont!=0)
            bullet_cont--;

        if(despausado < 4)
            despausado++;

        if(outmenu < 4)
            outmenu++;

        if(inimigos_da_fase==0)
        {
            game=1;
            fase++;
            SDL_Delay(2000);
        }

        for(k=0; k<max_inimigos; k++)
        {
            if(muda[k]>0)
            muda[k]--;
        }

        if(cont_surgir>0)
            cont_surgir--;
        else
            cont_surgir=300;

        if(cont_morte<100)
            cont_morte++;

        if(tempo_arma > 0)
            tempo_arma--;
        else
        {
            bullet_frame.x=0;
            gun = 10;
        }

        SDL_Delay(30);
    }


    //Liberar as imagens da memória
    SDL_FreeSurface(menuBackGround);
    SDL_FreeSurface(menupausa);
    SDL_FreeSurface(Start);
    SDL_FreeSurface(fundo);
    SDL_FreeSurface(fundo_terra);
    SDL_FreeSurface(player);
    SDL_FreeSurface(bullet);
    SDL_FreeSurface(gameover);
    SDL_FreeSurface(boss);

    SDL_FreeSurface(escrever_palavra);
    SDL_FreeSurface(escrever_pontos);
    SDL_FreeSurface(escrever_level);

    SDL_FreeSurface(coli_superior_es);
    SDL_FreeSurface(coli_superior_di);
    SDL_FreeSurface(coli_inferior_es);
    SDL_FreeSurface(coli_inferior_di);
    SDL_FreeSurface(coli_esquerda_sup);
    SDL_FreeSurface(coli_esquerda_inf);
    SDL_FreeSurface(coli_direita_sup);
    SDL_FreeSurface(coli_direita_inf);

    //Destruir janela
    SDL_DestroyWindow( window );

    TTF_CloseFont(fonte);
    TTF_Quit();

    //Encerrar o SDL
    SDL_Quit();

    return 0;
}

void atirador(int gun, int *enemy_alive, int enemy_frame_width, int enemy_frame_height, SDL_Rect enemy_position[], BULLET bullet_vet[], float velobull, SDL_Surface* bullet, SDL_Rect bullet_frame, SDL_Rect bullet_position[], SDL_Surface* tela)
{
    int j=0, i;

    for(j=0; j<MAX_BULLETCOUNT; j++)
    {
        if(bullet_vet[j].tiro == 1)
        {
            if(bullet_vet[j].posi==1 && bullet_position[j].y>60)
            {
                bullet_position[j].y -= velobull;
            }
            if(bullet_vet[j].posi==2 && bullet_position[j].x>60)
            {
                bullet_position[j].x -= velobull;
            }
            if(bullet_vet[j].posi==3 && bullet_position[j].y<SCREEN_HEIGHT-30)
            {
                bullet_position[j].y += velobull;
            }
            if(bullet_vet[j].posi==4)
            {
                bullet_position[j].x += velobull;
            }
            if(bullet_vet[j].posi==5)
            {
                bullet_position[j].y -= velobull;
                bullet_position[j].x += velobull;
            }
            if(bullet_vet[j].posi==6)
            {
                bullet_position[j].y += velobull;
                bullet_position[j].x += velobull;
            }
            if(bullet_vet[j].posi==7)
            {
                bullet_position[j].y -= velobull;
                bullet_position[j].x -= velobull;
            }
            if(bullet_vet[j].posi==8)
            {
                bullet_position[j].y += velobull;
                bullet_position[j].x -= velobull;
            }
        }

        for(i=0; i<MAX_ENEMY; i++)
        {
            if(!(enemy_position[i].x < bullet_position[j].x +6 && enemy_position[i].x +enemy_frame_width > bullet_position[j].x
                && enemy_position[i].y < bullet_position[j].y +6 && enemy_position[i].y +enemy_frame_height > bullet_position[j].y)
                && bullet_position[j].y > 60 && bullet_position[j].y+6 < SCREEN_HEIGHT-30 && bullet_position[j].x > 60 && bullet_position[j].x+6 < SCREEN_WIDTH-60)
            {
                SDL_BlitSurface(bullet, &bullet_frame, tela, &bullet_position[j]);
            }
            else if(enemy_position[i].x < bullet_position[j].x +6 && enemy_position[i].x +enemy_frame_width > bullet_position[j].x
                && enemy_position[i].y < bullet_position[j].y +6 && enemy_position[i].y +enemy_frame_height > bullet_position[j].y)
            {

                pontuacao += 10;
                inimigos_da_fase--;
                enemy_alive[i] = 0;
                enemy_position[i].x = 0;
                enemy_position[i].y = SCREEN_HEIGHT/2;
                bullet_vet[j].tiro=0;
                bullet_position[j].x= SCREEN_WIDTH+1;
                bullet_position[j].y= 0;
            }
            else
            {
                bullet_position[j].x= SCREEN_WIDTH+1;
                bullet_position[j].y= 0;
            }
        }
    }
}

//Começo código inimigo


void create_enemy(SDL_Rect enemy_position[], int *enemy_alive)
{
    //procura por inimigos mortos, se estiverem mortos, revive eles
    int ini_posi;
    int j = 0;

    ini_posi = rand()%4;

    while(enemy_alive[j] == 1 && j < max_inimigos)
    {
        j++;
    }

    if(enemy_alive[j] == 0 && inimigos_da_fase>j)
    {
        if(vivendo == 0)
        {
            enemy_alive[j] = 1;
            vivendo=5;
            if(ini_posi == 0)
            {
                enemy_position[j].y = 0;
                enemy_position[j].x = SCREEN_WIDTH/2;
            }
            else if(ini_posi == 1)
            {
                enemy_position[j].y = SCREEN_HEIGHT/2;
                enemy_position[j].x = 0;
            }
            else if(ini_posi == 2)
            {
                enemy_position[j].y = SCREEN_HEIGHT;
                enemy_position[j].x = SCREEN_WIDTH/2;
            }
            else if(ini_posi == 3)
            {
                enemy_position[j].y = SCREEN_HEIGHT/2;
                enemy_position[j].x = SCREEN_WIDTH;
            }
            
        }
    }

    if(vivendo>0)
        vivendo--;
}

void update_enemies(SDL_Rect coli_superior_di_posi, SDL_Rect coli_superior_es_posi, SDL_Rect coli_inferior_di_posi, SDL_Rect coli_inferior_es_posi, SDL_Rect coli_direita_sup_posi, SDL_Rect coli_direita_inf_posi, SDL_Rect coli_esquerda_sup_posi, SDL_Rect coli_esquerda_inf_posi,
    BULLET bullet_vet[], int *enemy_alive, SDL_Rect enemy_position[], SDL_Rect player_position, float vele, SDL_Surface* enemy, SDL_Rect enemy_frame[], SDL_Surface* tela, int enemy_frame_width, int enemy_frame_height, SDL_Rect bullet_position[])
{
    // vai procurando dentre todos os inimigos que estao vivos se eles estão na posição do player, se não
    // vai encrementando ou decrescendo sua posição até alcançalo
    // ""Falta o inimigo morrer caso o tiro encoste nele""

    int j;
    for(j=0; j < max_inimigos; j++)
    {
        if(muda[j]==0)
        {
            muda[j] = 10;
            ene_posi[j]=rand()%4;
        }
        // melhorar o modo aleatorio dos inimigos
        if(enemy_alive[j] == 1)
        {
            if(enemy_position[j].x < (player_position.x +player_position.w)*4 && enemy_position[j].x +enemy_frame_width > player_position.x*4
            && enemy_position[j].y < (player_position.y +player_position.h)*4 && enemy_position[j].y +enemy_frame_height > player_position.y*4)
            {
                if(enemy_position[j].y < player_position.y
                && (coli_esquerda_inf_posi.y > enemy_position[j].y+enemy_position[j].h
                || coli_direita_inf_posi.y > enemy_position[j].y+enemy_position[j].h 
                || coli_inferior_es_posi.y > enemy_position[j].y+enemy_position[j].h 
                || coli_inferior_di_posi.y > enemy_position[j].y+enemy_position[j].h))
                {
                    if(andar_inimigo ==2)
                    {
                        enemy_frame[j].y = 0;
                        enemy_frame[j].x = enemy_frame_width;
                    }
                    if(andar_inimigo == 0)
                    {
                        enemy_frame[j].y = 0;
                        enemy_frame[j].x = 2*enemy_frame_width;   
                    }

                    enemy_position[j].y +=vele;
                }
                if(enemy_position[j].x < player_position.x &&
                (coli_direita_sup_posi.x > enemy_position[j].x + enemy_frame_width
                || coli_direita_inf_posi.x > enemy_position[j].x + enemy_frame_width 
                || coli_superior_di_posi.x > enemy_position[j].x + enemy_frame_width 
                || coli_inferior_di_posi.x > enemy_position[j].x + enemy_frame_width))
                {
                    if(andar_inimigo ==2)
                    {
                        enemy_frame[j].y = 6*enemy_frame_height;
                        enemy_frame[j].x = enemy_frame_width;
                    }
                    if(andar_inimigo == 0)
                    {
                        enemy_frame[j].y = 6*enemy_frame_height;
                        enemy_frame[j].x = 2*enemy_frame_width;   
                    }
                    enemy_position[j].x +=vele;
                }
                if(enemy_position[j].y > player_position.y &&
                (coli_esquerda_sup_posi.y+coli_esquerda_sup_posi.h < enemy_position[j].y
                || coli_direita_sup_posi.y+coli_direita_sup_posi.h < enemy_position[j].y 
                || coli_superior_es_posi.y+coli_superior_es_posi.h < enemy_position[j].y 
                || coli_superior_di_posi.y+coli_superior_di_posi.h < enemy_position[j].y))
                {
                    if(andar_inimigo ==2)
                    {
                        enemy_frame[j].y = 4*enemy_frame_height;
                        enemy_frame[j].x = enemy_frame_width;
                    }
                    if(andar_inimigo == 0)
                    {
                        enemy_frame[j].y = 4*enemy_frame_height;
                        enemy_frame[j].x = 2*enemy_frame_width;   
                    }
                    enemy_position[j].y -=vele;
                }
                if(enemy_position[j].x > player_position.x &&
                (coli_esquerda_sup_posi.x+coli_esquerda_sup_posi.w < enemy_position[j].x
                || coli_esquerda_inf_posi.x+coli_esquerda_inf_posi.w < enemy_position[j].x 
                || coli_superior_es_posi.x+coli_superior_es_posi.w < enemy_position[j].x 
                || coli_inferior_es_posi.x+coli_inferior_es_posi.w < enemy_position[j].x))
                {
                    if(andar_inimigo ==2)
                    {
                        enemy_frame[j].y = 2*enemy_frame_height;
                        enemy_frame[j].x = enemy_frame_width;
                    }
                    if(andar_inimigo == 0)
                    {
                        enemy_frame[j].y = 2*enemy_frame_height;
                        enemy_frame[j].x = 2*enemy_frame_width;   
                    }
                    enemy_position[j].x -=vele;
                }
            }

            else
            {
                if(enemy_position[j].y > player_position.y &&
                (coli_esquerda_sup_posi.y+coli_esquerda_sup_posi.h < enemy_position[j].y
                || coli_direita_sup_posi.y+coli_direita_sup_posi.h < enemy_position[j].y 
                || coli_superior_es_posi.y+coli_superior_es_posi.h < enemy_position[j].y 
                || coli_superior_di_posi.y+coli_superior_di_posi.h < enemy_position[j].y))
                {
                    switch(ene_posi[j])
                    {
                    case 0 : enemy_position[j].y -=vele;
                        break;

                    case 1 : enemy_position[j].y -=vele;
                        break;

                    case 2 : enemy_position[j].y -=vele;
                        break;

                    case 3 : enemy_position[j].y +=vele;
                        break;
                    }

                    if(ene_posi[j] == 3)
                    {
                        enemy_frame[j].y = 0;

                         if(andar_inimigo ==2)
                        {
                            enemy_frame[j].x = enemy_frame_width;
                        }
                        if(andar_inimigo == 0)
                        {
                            enemy_frame[j].x = 2*enemy_frame_width;   
                        }
                    }
                    else
                    {
                        enemy_frame[j].y = 4*enemy_frame_height;

                        if(andar_inimigo ==2)
                        {
                            enemy_frame[j].x = enemy_frame_width;
                        }
                        if(andar_inimigo == 0)
                        {
                            enemy_frame[j].x = 2*enemy_frame_width;   
                        }
                    }
                }
                else if(enemy_position[j].y < player_position.y
                && (coli_esquerda_inf_posi.y > enemy_position[j].y+enemy_position[j].h
                || coli_direita_inf_posi.y > enemy_position[j].y+enemy_position[j].h 
                || coli_inferior_es_posi.y > enemy_position[j].y+enemy_position[j].h 
                || coli_inferior_di_posi.y > enemy_position[j].y+enemy_position[j].h))
                {
                    switch(ene_posi[j])
                    {
                    case 0 : enemy_position[j].y +=vele;
                        break;

                    case 1 : enemy_position[j].y +=vele;
                        break;

                    case 2 : enemy_position[j].y +=vele;
                        break;

                    case 3 : enemy_position[j].y -=vele;
                        break;
                    }
                    if(ene_posi[j] == 3)
                    {
                        enemy_frame[j].y = 4*enemy_frame_height;

                        if(andar_inimigo ==2)
                        {
                            enemy_frame[j].x = enemy_frame_width;
                        }
                        if(andar_inimigo == 0)
                        {
                            enemy_frame[j].x = 2*enemy_frame_width;   
                        }
                    }
                    else
                    {
                        enemy_frame[j].y = 0;

                        if(andar_inimigo ==2)
                        {
                            enemy_frame[j].x = enemy_frame_width;
                        }
                        if(andar_inimigo == 0)
                        {
                            enemy_frame[j].x = 2*enemy_frame_width;   
                        }
                    }
                }
                if(enemy_position[j].x > player_position.x &&
                (coli_esquerda_sup_posi.x+coli_esquerda_sup_posi.w < enemy_position[j].x
                || coli_esquerda_inf_posi.x+coli_esquerda_inf_posi.w < enemy_position[j].x 
                || coli_superior_es_posi.x+coli_superior_es_posi.w < enemy_position[j].x 
                || coli_inferior_es_posi.x+coli_inferior_es_posi.w < enemy_position[j].x))
                {
                    switch(ene_posi[j])
                    {
                    case 0 : enemy_position[j].x -=vele;
                        break;

                    case 1 : enemy_position[j].x -=vele;
                        break;

                    case 2 : enemy_position[j].x -=vele;
                        break;

                    case 3 : enemy_position[j].x +=vele;
                        break;
                    }
                    if(ene_posi[j] == 3)
                    {
                        enemy_frame[j].y = 6*enemy_frame_height;
                        
                        if(andar_inimigo == 2)
                        {
                            enemy_frame[j].x = enemy_frame_width;
                        }
                        if(andar_inimigo == 0)
                        {
                            enemy_frame[j].x = 2*enemy_frame_width;   
                        }
                    }
                    else
                    {
                        enemy_frame[j].y = 2*enemy_frame_height;
                        
                        if(andar_inimigo == 2)
                        {
                            enemy_frame[j].x = enemy_frame_width;
                        }
                        if(andar_inimigo == 0)
                        {
                            enemy_frame[j].x = 2*enemy_frame_width;   
                        }
                    }
                }
                else if(enemy_position[j].x < player_position.x &&
                (coli_direita_sup_posi.x > enemy_position[j].x + enemy_frame_width
                || coli_direita_inf_posi.x > enemy_position[j].x + enemy_frame_width 
                || coli_superior_di_posi.x > enemy_position[j].x + enemy_frame_width 
                || coli_inferior_di_posi.x > enemy_position[j].x + enemy_frame_width))
                {
                    switch(ene_posi[j])
                    {
                    case 0 : enemy_position[j].x +=vele;
                        break;

                    case 1 : enemy_position[j].x +=vele;
                        break;

                    case 2 : enemy_position[j].x +=vele;
                        break;

                    case 3 : enemy_position[j].x -=vele;
                        break;
                    }
                    if(ene_posi[j] == 3)
                    {
                        enemy_frame[j].y = 2*enemy_frame_height;
                        
                        if(andar_inimigo ==2)
                        {
                            enemy_frame[j].x = enemy_frame_width;
                        }
                        if(andar_inimigo == 0)
                        {
                            enemy_frame[j].x = 2*enemy_frame_width;   
                        }
                    }
                    else
                    {
                        enemy_frame[j].y = 6*enemy_frame_height;

                        if(andar_inimigo ==2)
                        {
                            enemy_frame[j].x = enemy_frame_width;
                        }
                        if(andar_inimigo == 0)
                        {
                            enemy_frame[j].x = 2*enemy_frame_width;   
                        }
                    }
                }

            }

            SDL_BlitSurface(enemy, &enemy_frame[j], tela, &enemy_position[j]);
        }
    }

    if(cont_morte == 100)
    {
        if(andar_inimigo < 2)
        {
            andar_inimigo++;
        }
        else
            andar_inimigo=0;
    }

}

void boss_up(int boss_alive, SDL_Surface* tela, SDL_Surface* boss, SDL_Rect coli_superior_di_posi, SDL_Rect coli_superior_es_posi, SDL_Rect coli_inferior_di_posi, SDL_Rect coli_inferior_es_posi, SDL_Rect coli_direita_sup_posi, SDL_Rect coli_direita_inf_posi, SDL_Rect coli_esquerda_sup_posi, SDL_Rect coli_esquerda_inf_posi, float velboss, SDL_Rect boss_position, SDL_Rect boss_frame, SDL_Rect player_position, int BOSS_FRAME_WIDTH, int BOSS_FRAME_HEIGHT)
{
    if(boss_alive == 1)
    {   
        if(boss_position.y < player_position.y
        && (coli_esquerda_inf_posi.y > boss_position.y+boss_position.h
        || coli_direita_inf_posi.y > boss_position.y+boss_position.h 
        || coli_inferior_es_posi.y > boss_position.y+boss_position.h 
        || coli_inferior_di_posi.y > boss_position.y+boss_position.h))
        {
            boss_frame.y = 0;
            if(and_boss ==2)
            {
                boss_frame.x = 0;
            }
            if(and_boss == 0)
            {
                boss_frame.x = BOSS_FRAME_WIDTH;   
            }

            boss_position.y += velboss;
        }
        if(boss_position.x < player_position.x &&
        (coli_direita_sup_posi.x > boss_position.x + BOSS_FRAME_WIDTH
        || coli_direita_inf_posi.x > boss_position.x + BOSS_FRAME_WIDTH 
        || coli_superior_di_posi.x > boss_position.x + BOSS_FRAME_WIDTH 
        || coli_inferior_di_posi.x > boss_position.x + BOSS_FRAME_WIDTH))
        {
            boss_frame.y = 2*BOSS_FRAME_HEIGHT;
                
            if(and_boss ==2)
            {
                boss_frame.x = 0;
            }
            if(and_boss == 0)
            {
                boss_frame.x = BOSS_FRAME_WIDTH;   
            }
            boss_position.x += velboss;
        }
        if(boss_position.y > player_position.y &&
        (coli_esquerda_sup_posi.y+coli_esquerda_sup_posi.h < boss_position.y
        || coli_direita_sup_posi.y+coli_direita_sup_posi.h < boss_position.y 
        || coli_superior_es_posi.y+coli_superior_es_posi.h < boss_position.y 
        || coli_superior_di_posi.y+coli_superior_di_posi.h < boss_position.y))
        {
            boss_frame.y = 3*BOSS_FRAME_HEIGHT;

            if(and_boss ==2)
            {
                boss_frame.x = 0;
            }
            if(and_boss == 0)
            {
                boss_frame.x = BOSS_FRAME_WIDTH;   
            }
            boss_position.y -= velboss;
        }
        if(boss_position.x > player_position.x &&
        (coli_esquerda_sup_posi.x+coli_esquerda_sup_posi.w < boss_position.x
        || coli_esquerda_inf_posi.x+coli_esquerda_inf_posi.w < boss_position.x 
        || coli_superior_es_posi.x+coli_superior_es_posi.w < boss_position.x 
        || coli_inferior_es_posi.x+coli_inferior_es_posi.w < boss_position.x))
        {
            boss_frame.y = BOSS_FRAME_HEIGHT;
            if(and_boss ==2)
            {
                boss_frame.x = 0;
            }
            if(and_boss == 0)
            {
                boss_frame.x = BOSS_FRAME_WIDTH;   
            }
            boss_position.x -= velboss;
        }

        if(and_boss < 2)
        {
            and_boss++;
        }
        else
            and_boss=0;

        SDL_BlitSurface(boss, &boss_frame, tela, &boss_position);
    }
}