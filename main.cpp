#include "ola.cpp"

int main(){
    system("CLS");
    srand(time(NULL));
    Logs *L = L->getInstance();
    OLA ola;
    CabTypes C[] = {ct_Mini,ct_Mini,ct_Sedan,ct_Sedan,ct_Prime};
    ola.driverCabLinkage.cabs = ola.driverCabLinkage.createCabs(C);
    ola.driverCabLinkage.cabAllotment();
    SignIn SI;
    SignUp SU;
    LogIn* LI[] = {&SI,&SU};
    FrontEndInterface F;
    Coupon Co[] = {Coupon("WX1234", 100),
                  Coupon("MX1244", 50),
                  Coupon("ZM1252", 200),
                  Coupon("KAO182", 30),
                  Coupon("LAPY123", 100)
              };
    F.welcome();
    Computation C1,C2;
    try{
       while(running){
              while(flag1){
              F.menu();
              cout << "Enter your choice:";
              cin >> choice1;
              system("CLS");
              switch(choice1){
              case 1:if(ola.customer[0]->logInFlag == 0){
                            status = ola.loginSignUpPortal(LI[0]);
                            if(status == 1){
                                   Sleep(200);
                                   system("CLS");
                                   flag1 = 0;
                                   flag2 = 1;
                            }
                     }
                     else{
                        cout << "Someone has logged in. Please try after sometime" << endl;
                     }
                     break;
              case 2:status = ola.loginSignUpPortal(LI[1]);
                            if(status == 1){
                            Sleep(200);
                            system("CLS");
                            flag1 = 0;
                            flag2 = 1;
                     }
                     break;
              case 3:F.menu();
                     cout << "\nThank you for using ola cabs. Have a nice day\n\n\n";
                     status = ola.exitDump();
                     flag1 = 0;
                     flag2 = 0;
                     running = 0;
                     break;
              default:system("CLS");
                     cout << "Invalid choice!! Re-enter\n\n";
              }
              }
              while(flag2){
              F.login_menu(ola.customer[ola.index]->name);
              cout << "Enter your choice:";
              cin >> choice4;
              cout << "\n\n";
              switch(choice4){
                     case 1:ola.customer[ola.index]->display();
                            cout << "Enter ANY KEY to exit\n";
                            getchar();
                            if(getchar()){
                                   system("CLS");
                            }
                            break;
                     case 2:status=ola.customer[ola.index]->displayRideHistory();
                            if(status!=1){
                            printf("NO ride history found\n\n");
                            Sleep(3000);
                            system("CLS");
                            }
                            else{
                            cout << "Press any key to go back";
                            getchar();
                            if(getchar()){
                                   system("CLS");
                            }
                            }
                            break;
                     case 3:ola.printLocations(C1);
                            ola.bookCabs(C1,C2,Co);
                            break;
                     case 4:status = ola.logout();
                            if(status!=1){
                            Sleep(3000);
                            system("CLS");
                            }
                            system("CLS");
                            cout << "Successfully logged out" << endl;
                            Sleep(2000);
                            flag2 = 0;
                            flag1 = 1;
                            system("CLS");
                            break;
                     default:system("CLS");
                            printf("Invalid choice!! Re-enter your choice\n\n");
                            
              }
              }
       }
    }
    catch(ErrorHandling &E){
       cout << E.what() << endl;
    }
    L->close_log();
    return 0;
}