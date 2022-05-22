#include "CommonFunc.h"
#include "CommonFunc.cpp"
#include "BaseObject.h"
#include "BaseObject.cpp"
#include "game_map.h"
#include "game_map.cpp"
#include "MainObject.h"
#include "MainObject.cpp"
#include "ImpTimer.h"
#include "ImpTimer.cpp"
#include "BulletObject.h"
#include "BulletObject.cpp"
#include "ThreatsObject.h"
#include "ThreatsObject.cpp"
#include "ExplosionObject.h"
#include "ExplosionObject.cpp"
#include "TextObject.h"
#include "TextObject.cpp"
#include "PlayerPower.h"
#include "PlayerPower.cpp"
#include "Geometric.h"
#include "Geometric.cpp"

BaseObject g_background;
TTF_Font* font_time = NULL;
TTF_Font* font = NULL;
const SDL_Color BLACKCOLOR = {0, 0, 0, 0};

bool InitData(){
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Game Shooting Monster - 21020345", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (g_window == NULL){
        success = false;
    }
    else{
        g_screen = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL) success = false;
        else{
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }

        if(TTF_Init() == -1){
            success = FALSE;
        }
        font_time = TTF_OpenFont("font//dlxfont_.ttf",15);
        font = TTF_OpenFont("font//dlxfont_.ttf", 30);
        if(font_time == NULL){
            success = FALSE;
        }
    }
        return success;
}



bool LoadBackGround(){
    bool ret = g_background.LoadImg("img//background.png", g_screen);
    if(ret == false)
        return false;

    else return true;
}
void close(){
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

void showBox(bool fatal) {
    SDL_Delay(500);
    SDL_Event e;
    TextObject text[4];
    text[0].SetText("Congratulation! You Win");
    text[1].SetText("You Lost!");
    text[2].SetText("Press to SPACE to replay ");
    text[3].SetText("or ESC to exit game!");
    for(int i = 0; i < 4; i++) {
        int leng = text[i].GetText().length() * 30;
        text[i].SetRect((SCREEN_WIDTH - leng) / 2, 150 + 60*i);
        text[i].SetColor(BLACKCOLOR);
    }
    for(int i = 0; i < 2; i++) {
        if((fatal && i == 0) || (!fatal && i == 1) || i >= 2) {
            text[i].LoadFromRenderText(font, g_screen);
            text[i].RenderText(g_screen, text[i].getPosX(), text[i].getPosY());
        }
    }
    SDL_RenderPresent(g_screen);
    SDL_Delay(5000);
    close();
    exit(1);
}
std::vector<ThreatsObject*> MakeThreadList(){
    std::vector<ThreatsObject*> list_threats;


    ThreatsObject* dynamic_threats = new ThreatsObject[20];
    for(int i=0; i<20; i++){
        ThreatsObject* p_threat = (dynamic_threats + i);
        if(p_threat != NULL){
            p_threat ->LoadImg("img//threat_left.png",g_screen);
            p_threat ->set_clips();
            p_threat -> set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat ->set_x_pos(500 + i* 500);
            p_threat ->set_y_pos(200);

            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat -> get_x_pos() + 60;
            p_threat -> SetAnimationPos(pos1, pos2);
             p_threat -> set_input_left(1);

            list_threats.push_back(p_threat);
         }
    }

    ThreatsObject* threats_obj = new ThreatsObject[20];
    for(int i=0; i < 20; i++){
        ThreatsObject* p_threat = ( threats_obj + i );
        if(p_threat != NULL){
            p_threat -> LoadImg("img//threat_level.png", g_screen);
            p_threat -> set_clips();
            p_threat -> set_x_pos(i*1200 + 700);
            p_threat -> set_y_pos(250);
            p_threat ->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat ->set_input_left(0);

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);

            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}



int main(int argc, char* argv[])
{
    ImpTimer fps_timer;

    if(InitData() == false)
        return -1;

    if(LoadBackGround() == false)
        return -1;

    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImg("img//player_right.png", g_screen);
    p_player.set_clips();

    PlayerPower player_power;
    player_power.Init(g_screen);

    PlayerMoney player_money;
    player_money.Init(g_screen);
    player_money.SetPos(SCREEN_WIDTH*0.5 - 300, 8);

    std::vector<ThreatsObject*> threats_list = MakeThreadList();

    ExplosionObject exp_threat;
    ExplosionObject exp_main;


    bool tRet = exp_threat.LoadImg("img//ex3.png", g_screen);
    if(!tRet ) return -1;
    exp_threat.set_clip();

    bool mRet = exp_main.LoadImg("img//ex3.png", g_screen);
    if(!mRet) return -1;
    exp_main.set_clip();

    int num_die = 0;

    // Time Text
    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);

    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);
    UINT mark_value = 0;

    TextObject money_game;
    money_game.SetColor(TextObject::WHITE_TEXT);

    bool is_quit = false;
    while(!is_quit) {
        fps_timer.start();
        while(SDL_PollEvent(&g_event) != 0){
            if(g_event.type == SDL_QUIT){
                is_quit = true;
            }

            p_player.HandelInputAction(g_event, g_screen);
        }

        SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        // game_map.DrawMap(g_screen);
        Map map_data = game_map.getMap();
        if(p_player.get_destination()) {
            showBox(true);
        }
        p_player.HandleBullet(g_screen);
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        //Draw Geometric
        GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40);
        ColorData color_data(0, 80, 150);
        Geometric::RenderRectangle(rectangle_size, color_data, g_screen);

        GeometricFormat outline_size(1, 1, SCREEN_WIDTH - 1 , 38);
        ColorData color_data2(255,255,255);
        Geometric::RenderOutline(outline_size, color_data2, g_screen);

        player_power.Show(g_screen);
        player_money.Show(g_screen);

        for(int i=0; i < threats_list.size(); i++){
            ThreatsObject* p_threat = threats_list.at(i);
            if(p_threat != NULL){
                p_threat -> SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat -> ImpMoveType(g_screen);
                p_threat -> DoPlayer(map_data);
                p_threat -> MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat -> Show(g_screen);

                SDL_Rect rect_player = p_player.GetRectFrame();
                bool bCol1 = false;
                std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list_();
                for(int jj = 0; jj < tBullet_list.size(); jj++){
                    BulletObject* pt_bullet = tBullet_list.at(jj);
                    if(pt_bullet !=  NULL){
                        bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
                        if(bCol1){
                            p_threat->RemoveBullet(jj);
                            break;
                        }
                    }
                }
                SDL_Rect rect_threat = p_threat->GetRectFrame();
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player,rect_threat);

                if(bCol1 == true || bCol2 == true){
                    int width_exp_frame = exp_main.get_frame_width();
                    int height_exp_height = exp_main.get_frame_heigh();
                    for(int ex = 0; ex < 8; ex++){
                        int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
                        int y_pos = (p_player.GetRect().y + p_player.get_frame_heigh()*0.5) - height_exp_height*0.5;

                        exp_main.set_frame(ex);
                        exp_main.SetRect(x_pos,y_pos);
                        exp_main.Show(g_screen);
                        SDL_RenderPresent(g_screen);
                    }
                    num_die++;
                    if(num_die <= 3){
                        p_player.SetRect(0,0);
                        p_player.set_come_back_time(60);
                        SDL_Delay(1000);
                        player_power.Decrease();
                        player_power.Render(g_screen);
                        continue;
                    }
                    else{
                        // if(MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK){
                        p_threat ->Free();
                        showBox(false);
                        return 0;
                    // }
                    }
                }
            }
        }

        int frame_exp_width = exp_threat.get_frame_width();
        int frame_exp_heigh = exp_threat.get_frame_heigh();
        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for(int r = 0; r < bullet_arr.size(); r++){
            BulletObject* p_bullet = bullet_arr.at(r);
            if(p_bullet != NULL){
                for(int t= 0; t < threats_list.size(); t++){
                    ThreatsObject* obj_threat = threats_list.at(t);
                    if(obj_threat != NULL){
                        SDL_Rect tRect;
                        tRect.x = obj_threat->GetRect().x;
                        tRect.y = obj_threat->GetRect().y;
                        tRect.w = obj_threat->get_width_frame();
                        tRect.h = obj_threat->get_height_frame();

                        SDL_Rect bRect = p_bullet->GetRect();

                        bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

                        if(bCol){
                            mark_value++;
                            for(int ex = 0; ex < NUM_FRAME_EXP; ex ++){
                                int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_width*0.5;

                                exp_threat.set_frame(ex);
                                exp_threat.SetRect(x_pos,y_pos);
                                exp_threat.Show(g_screen);
                            }
                            p_player.RemoveBullet(r);
                            obj_threat->Free();
                            threats_list.erase(threats_list.begin() + t);
                        }
                    }
                }
            }
        }

        // Show game time
        std::string str_time = "Time: ";
        Uint32 time_val = SDL_GetTicks()/1000;
        Uint32 val_time = 300 - time_val;
        if(val_time <=0){
             // if(MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK){
                      is_quit = true;
                      break;
                    // }
        }
        else{
            std::string str_val = std::to_string(val_time);
            str_time += str_val;

            time_game.SetText(str_time);
            time_game.LoadFromRenderText(font_time, g_screen);
            time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
        }

        std::string val_str_mark = std::to_string(mark_value);
        std::string strMark("Mark: ");
        strMark += val_str_mark;

        mark_game.SetText(strMark);
        mark_game.LoadFromRenderText(font_time, g_screen);
        mark_game.RenderText(g_screen, SCREEN_WIDTH*0.5-50, 15);

       int  money_count = p_player.get_money_count();
       std::string money_string = std::to_string(money_count);

       money_game.SetText(money_string);
       money_game.LoadFromRenderText(font_time, g_screen);
       money_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 250, 15);

        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND; // tinh theo mili giay

        if(real_imp_time < time_one_frame){
             int delay_time = time_one_frame - real_imp_time;
             if(delay_time >= 0){
                SDL_Delay(delay_time);
             }
        }

    }
    for(int i=0; i< threats_list.size(); i++){
        ThreatsObject* p_threat = threats_list.at(i);
        if(p_threat != NULL){
            p_threat->Free();
            p_threat = NULL;
        }
    }
    threats_list.clear();
    close();
    return 0;
}
