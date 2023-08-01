#include "SDL2_APP.h"


SDL2_APP::SDL2_APP() {
    Surf_Display = NULL;
    Running = true;


}

void SDL2_APP::NewGame() {
    dealer->Clear();
    dealer->DealerSpecific();
    for (int i = 0; i < player.size(); i++) {
        player[i]->Clear();
    }
    PlayerCounter = 0;
}



bool SDL2_APP::OnInit() {
    if (SDL_Init(0) < 0) {
        return false;
    }


    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) {
        return false;
    }

    SDL_SetWindowTitle(window, "My Game !!!");

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    /////////////////////////////////////

    colorobj = std::make_shared<ColoredObject>(renderer,255, 0, 255, 255, 0, 0, WIDTH, HEIGHT);
   
    //button = std::make_shared<Button>(renderer, NEW_HAND, 30, 20);
    ////card = std::make_shared<Card>(renderer, 52, 30, 100);
    //deck1 = std::make_shared<deck>(renderer,20,50);

    //deck2 = std::make_shared<deck>(renderer, 200, 50);

    //text = std::make_shared<Text>(renderer,1000 ,200, 300);

    //digit = std::make_shared<Digit>(renderer, 9, 30, 150);
    dealer = std::make_shared<Player>(renderer, 200, 150);
    //dealer->SetActive();
    dealer->ShowButtonsFalse();
    dealer->DealerSpecific();
    player.push_back(std::make_shared<Player>(renderer, 200, 550));
    player[0]->SetActive();
    
    return true;
}



int SDL2_APP::OnExecute() {
    if (OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while (Running) {
        while (SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}




void SDL2_APP::OnEvent(SDL_Event * Event) {


    //std::vector<std::shared_ptr<Player>>::iterator player_it= player.begin();

    if (PlayerCounter < player.size()) {
        if (player[PlayerCounter]->IsActive()) {
            player[PlayerCounter]->OnEvent(Event);
        }
        else {
            player[PlayerCounter++]->ShowButtonsFalse();
            if (!PlayerCounter == player.size()) {
                player[PlayerCounter]->SetActive();
            }
        }

    }
    

    if (PlayerCounter == player.size()) {
        dealer->SetActive();
        dealer->ShowButtonsFalse();
        while (dealer->GetPoints() < 17) {
            dealer->AddCard();
        }
        Winner();
        NewGameCond = 1;

       
    }

    


    ////////////////////////////////////////
    if (Event->quit.type == ::SDL_QUIT) {
        Running = false;
    }
  




}

void SDL2_APP::OnLoop() {
    if (PlayerCounter < player.size()) {
        if (player[PlayerCounter]->GetPoints()>21) {
            player[PlayerCounter]->SetPassive();
        }

    }

    
}


void SDL2_APP::OnRender() {
    //
    colorobj->Draw();
    

    dealer->Draw();

    player[0]->Draw();

    if (NewGameCond >= 1) {
        NewGameCond++;
        
    }
    if (NewGameCond == 30) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        
        NewGame();
        player[0]->SetActive();
        PlayerCounter = 0;
        NewGameCond = 0;
    }
    SDL_RenderPresent(renderer);
   
}

void SDL2_APP::Winner() {
    for (int i = 0; i < player.size(); i++) {
        if (player[i]->GetMoney() < 0) {
            player[0]->PlayerEnd();
        }
        else {
            if (player[i]->GetPoints() > 21) {
                player[i]->SetMoneyL();
            }
            else {
                if (dealer->GetPoints() > 21) {
                    player[i]->SetMoneyW();
                }
                else {
                    if (dealer->GetPoints() > player[i]->GetPoints()) {
                        player[i]->SetMoneyL();
                    }
                    else {
                        if (dealer->GetPoints() < player[i]->GetPoints()) {
                            player[i]->SetMoneyW();
                        }
                    }
                }
            }

        }

    }
}

void SDL2_APP::OnCleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}



SDL2_APP::~SDL2_APP() {
    //
}




