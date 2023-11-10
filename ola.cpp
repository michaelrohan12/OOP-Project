#include "ola.h"

class Logs{
private:
    static Logs* instance;
    FILE* flog;
    Logs() {
        flog = fopen("log.txt","a+");

        // If unable to open the file, alert the user
        if(flog == NULL)
            cout << "LOG File not found. No log status will be captured.";
        else{
            fprintf(flog,"%s","_________________START OF PROCESS_________________");
            fprintf(flog,"%s","\n\n");
        }
    }
public:
    static Logs* getInstance(){
        if(!instance)
            instance = new Logs;
        return instance;
    }
    void write_log(const char *function_name,const char *status,const char *message){
        // Write the appropriate log message with associated run time
        time_t mytime = time(NULL);
        fprintf(flog,"%s %s : %s --->%s\n\n",ctime(&mytime),function_name,status,message);
    }
    void close_log(){
        if(flog!=NULL){
            // Add a message to indicate end of a iteration
            fprintf(flog,"%s","_________________END OF PROCESS_________________");
            fprintf(flog,"%s","\n\n");

            // Close the file pointer
            fclose(flog);
        }
    }
    int file_empty_check(char *filename)
    {

        // Declaring "stat" a system call to know about content of file.
        struct stat filestat;
        stat(filename,&filestat);
    
        // Variables to hold messages
        char message_failure[40];
        char message_success[40];
    
        strcpy(message_failure, filename);
        strcat(message_failure, "is empty. No data available");
    
        strcpy(message_success,filename);
        strcat(message_success," has content.");
    
        //check size of file and return appropriate status.
        if(filestat.st_size == 0){
            write_log("file_empty_check","FILE_EMPTY_ERROR",message_failure);
            return FILE_EMPTY_ERROR;
        }
        else{
            write_log("file_empty_check","SUCCESS",message_success);
            return SUCCESS;
        }
    }
};

Logs *Logs::instance = 0;

class FrontEndInterface{
public:
    void welcome(){
        system("color 1E"); //Setting The Color Of Console
        cout << endl;
        cout.flush();
        cout << setw(80);
        cout << "\t******************************\n"<< setw(80);
        cout << "\t*          WELCOME           *\n"<< setw(80);
        cout << "\t*            To              *\n"<< setw(80);
        cout << "\t*           OLA              *\n"<< setw(80);
        cout << "\t*  Book a City Taxi to your  *\n"<< setw(80);
        cout << "\t*   destination in town      *\n"<< setw(80);
        cout << "\t******************************\n"<< setw(80);
        cout << "\n\n\n";
        cout << "\tLOADING ";
        for(int i=0;i<7;i++){
            Sleep(200);//For Pause
            cout << "<";
            Sleep(200);//For Pause
            cout << ">";
        }

        Sleep(200);//For Pause
        cout << "\n\n\tSUCCESSFUL\n";

        Sleep(2000);//For Pause
        system("CLS");//To Clear The Screen
    }
    void menu(){
      cout << "\t************************\n";
      cout << "\t*      OLA CABS        *\n";
      cout << "\t************************\n\n";

      cout << "\t************************\n";
      cout << "\t*<1>  USER LOGIN       *\n";
      cout << "\t************************\n\n";

      cout << "\t************************\n";
      cout << "\t*<2>  USER SIGNUP      *\n";
      cout << "\t************************\n\n";

      cout << "\t************************\n";
      cout << "\t*<3>     EXIT          *\n";
      cout << "\t************************\n\n";
    }
    void login_menu(string name){
         cout << "\t*****************************\n";
         cout << "\t*        OLA CABS           *\n";
         cout << "\t*****************************\n\n";
         cout << "\t*****************************\n";
         cout << "\t*WELCOME," << name <<"               \n";
         cout << "\t*****************************\n\n";
         cout << "1.Profile Details\n";
         cout << "2.Ride History\n";
         cout << "3.Book a ride\n";
         cout << "4.Log Out\n";
    }
};

class ErrorHandling{
    public: 
    const char* message;
    ErrorHandling(const char* m):message(m) {}
    virtual const char* what() = 0;
};

class InvalidCoupon:public ErrorHandling
{
public:
    InvalidCoupon(const char* m):ErrorHandling(m){}
    const char* what()
    {
        return message;
    }
};

class UnAvailability:public ErrorHandling
{
public:
    UnAvailability(const char* m):ErrorHandling(m){}
    const char* what()
    {
        return message;
    }
};

class PaymentError:public ErrorHandling
{
public:
    PaymentError(const char* m):ErrorHandling(m){}
    const char* what()
    {
        return message;
    }
};

class Cabs{
public:
    int carNo;
    string carColor;
    double fuelCapacity;
    double fare;
    string cabType;
    Cabs(int cN,string cC,double fC,double f,string cT):carNo(cN),carColor(cC),fuelCapacity(fC),fare(f),cabType(cT) {}
    virtual void display(){
        cout << "Car Number:" << carNo <<endl;
        cout << "Car Color:" << carColor << endl;
        cout << "Fuel Capacity:" << fuelCapacity << endl;
        cout << "Fare:" << fare << endl;
    }
};

class Mini:public Cabs{
public:
    string vehicleType;
    Mini(int cN,string cC,double fC,double f,string cT,string vT):Cabs(cN,cC,fC,f,cT),vehicleType(vT) {}
    void display(){
        Cabs::display();
        cout << "Vehicle Type:" << vehicleType << endl; 
    }
};

class Sedan:public Cabs{
public:
    string vehicleType;
    Sedan(int cN,string cC,double fC,double f,string cT,string vT):Cabs(cN,cC,fC,f,cT),vehicleType(vT) {}
    void display(){
        Cabs::display();
        cout << "Vehicle Type:" << vehicleType << endl; 
    }
};

class Prime:public Cabs{
public:
    string vehicleType;
    Prime(int cN,string cC,double fC,double f,string cT,string vT):Cabs(cN,cC,fC,f,cT),vehicleType(vT) {}
    void display(){
        Cabs::display();
        cout << "Vehicle Type:" << vehicleType << endl; 
    }
};



class DriverProfile{
public:
    string name;
    long long phoneNo;
    bool status;
    string currentLocation;
    string vehicleType;
    DriverProfile():name(""),phoneNo(0),status(1),currentLocation("") {}
    void changeStatus(){
        !status;
    }
    void changeCurrentLocation(string location){
        currentLocation = location;
    }
    void display(){
        cout << "Driver Name:" << name << endl;
        cout << "Vehicle Type:" << vehicleType << endl;
        cout << "Phone No:" << phoneNo << endl;
        if(status == true)
            cout << "status:Unavailable" << endl;
        else 
            cout << "status:Available" << endl;
        cout << "Current Location:" << currentLocation << endl;
    }
};

enum CabTypes{
    ct_Mini,ct_Sedan,ct_Prime
};

class DriverCabLinkage{
public:
    static int driverCount;
    static int cabCount;
    vector<Cabs*> cabs;
    vector<DriverProfile*> drivers;
    static void count(){
        driverCount++;
    }
    void cabAllotment(){
        int i;
        for(i=0;i!=driverCount;i++)
            drivers[i]->vehicleType = cabs[i]->cabType;
    }
    int findDriver(string name){
        int i;
        for(i = 0;i<drivers.size();i++){
            if(drivers[i]->name == name)
                return i;
        }
    }
    void displayCabs(){
         cout << "Enter the cab of your choice\n";
         cout << "1.Mini\n2.Prime\n3.Sedan\n";
    }
    vector<Cabs*> createCabs(CabTypes C[]){
        FILE *fp;
        fp = fopen("Cabs.txt","r");
        vector<Cabs*> cabsList;
        int i = 0;
        while(!feof(fp)){
            if(C[i++] == ct_Mini){
                fscanf(fp,"%d %s %lf %lf %s %s",&temp1,temp2,&temp3,&temp4,temp5,temp6);
                cabsList.push_back(new Mini(temp1,(string)temp2,temp3,temp4,(string)temp5,(string)temp6));
            }
            else if(C[i++] == ct_Prime){
                fscanf(fp,"%d %s %lf %lf %s %s",&temp1,temp2,&temp3,&temp4,temp5,temp6);
                cabsList.push_back(new Prime(temp1,(string)temp2,temp3,temp4,(string)temp5,(string)temp6));
            }
            else if(C[i++] == ct_Sedan){
                fscanf(fp,"%d %s %lf %lf %s %s",&temp1,temp2,&temp3,&temp4,temp5,temp6);
                cabsList.push_back(new Sedan(temp1,(string)temp2,temp3,temp4,(string)temp5,(string)temp6));
            }
        }
        return cabsList;
    }
};

int DriverCabLinkage::driverCount = 0;

class Computation{
public:
    string* locations;
    float** distanceEstimate;
    float** timeEstimate;
    int locations_count;
    int locations_length = 100;
    Computation(){
        Logs *L = L->getInstance();
        FILE *fp;
        fp = fopen("locations_count.txt","r");
        if(fp == NULL) {
             L->write_log("load", "FILE_OPEN_ERROR", "Unable to open the locations_count file");
             cout << "Memory Allocation Failed\n";
        }

        fscanf(fp,"%d ",&locations_count);
        fclose(fp);

        int i = 0,j = 0,u,v;
        float t;

        //Column Dynamic allocation of locations using char* array
        locations = new string[locations_count];
        
        if(locations == NULL){
            L->write_log("locations_load", "MEMORY_ALLOCATION_ERROR", "Memory allocation failed");
            return ;
        }

        char temp[locations_length];

        fp = fopen("locations.txt","r");
        while(!feof(fp)){
            //Transfer of string from secondary memory to primary memory
            fgets(temp, locations_length,fp);
            if(locations_count != (i-1))
                temp[strlen(temp) - 1] = '\0';
            locations[i] = temp;
            i++;
        }
        fclose(fp);

        timeEstimate = new float*[locations_length];
        for(i=0;i<locations_count;i++)
        {
            timeEstimate[i] = new float[locations_length];
        }

        for(i=0;i<locations_count;i++){
            for(j=0;j<locations_count;j++){
                if(i == j)
                    timeEstimate[i][j]=0;
                else
                    timeEstimate[i][j]=MAX;
            }
        }

        fp = fopen("time_data.txt","r");
        while(!feof(fp)){
            fscanf(fp,"%d %d %f",&u,&v,&t);
            timeEstimate[u][v]=t;
            timeEstimate[v][u]=t;
        }
        fclose(fp);

        distanceEstimate = new float*[locations_length];
        for(i=0;i<locations_count;i++)
        {
            distanceEstimate[i] = new float[locations_length];
        }

        for(i=0;i<locations_count;i++){
            for(j=0;j<locations_count;j++){
                if(i==j)
                    distanceEstimate[i][j]=0;
                else
                    distanceEstimate[i][j]=MAX;
            }
        }

        fp = fopen("distance_data.txt","r");
        while(!feof(fp)){
            fscanf(fp,"%d %d %f",&u,&v,&t);
            distanceEstimate[u][v]=t;
            distanceEstimate[v][u]=t;
        }
        fclose(fp);
    }
    void driverETA(){
        for(int k=0;k<locations_count;k++){
            for(int i=0;i<locations_count;i++){
                for(int j=0;j<locations_count;j++)
                {
                    if((timeEstimate[i][k]+timeEstimate[k][j])<timeEstimate[i][j]){
                        timeEstimate[i][j]=timeEstimate[i][k]+timeEstimate[k][j];
                    }
                }
            }
        }
    }
    int searchLocation(string location){
        for(int i=0;i<locations_count;i++){
            if(location == locations[i])
                return i;
        }
        return -1;
    }
    void pathTrace(int destination,int *path){
        if(path[destination]==destination){
             cout << locations[destination];
             cout << "-";
             Sleep(1000);
             cout << "-";
             Sleep(1000);
             cout << "-";
             Sleep(1000);
             cout << ">";
             return;
        }
        pathTrace(path[destination],path);
        cout << locations[destination];
        cout << "-";
        Sleep(1000);
        cout << "-";
        Sleep(1000);
        cout << "-";
        Sleep(1000);
        cout << ">";
        return;
    }
    int minWeight(int a,int b,int* path,int source,int i)
    {
        if(a<b)
            return a;
        else{
            path[i]=source;
            return b;
        }
    }
    double shotestPath(string pickup,string destination){
        int source = searchLocation(pickup);
        int destinations = searchLocation(destination);
        int min_wt,min_index,flag1=1,flag2=1;
        int* path = new int[locations_count];
        int*  visited = new int[locations_count];
        float* time = new float[locations_count];

        float total = 0.0;
        memset(visited,0,locations_count*sizeof(int));
        for(int i=0;i<locations_count;i++)
            path[i] = source;
        for(int i=0;i<locations_count;i++){
            time[i] = timeEstimate[source][i];
        }
        visited[source]=1;
        while(flag1)
        {
            flag1=0;
            flag2=1;
            for(int i=0;i<locations_count;i++)
            {
                if(visited[i]==0){
                    flag1=1;
                    if(flag2){
                        flag2=0;
                        time[i] = minWeight(time[i],total+timeEstimate[source][i],path,source,i);
                        min_wt=time[i];
                        min_index=i;
                    }
                    else{
                        time[i] = minWeight(time[i],total+timeEstimate[source][i],path,source,i);
                        if(min_wt>time[i]){
                            min_wt=time[i];
                            min_index=i;
                        }
                    }
                }
            }
            if(flag1==0)
                break;
            visited[min_index]=1;
            source=min_index;
            total=min_wt;
        }
        pathTrace(destinations,path);
        cout << "You have Reached your Destination!!\n\n";
        cout << "Total time taken:" << time[destinations] <<" minutes\n\n";
        Sleep(2000);
        return time[destinations];
    }
    void displayLocations(){
        Logs* L = L->getInstance();
        cout << "The Locations are\n";
        for(int i=0;i<locations_count;i++){
            cout << locations[i] << "\n";
        }
        cout << "\n";
    
        L->write_log("print_locations", "SUCCESS", "Successfully displayed the locations.");
    }
};

class RideHistory
{
public:
    char pickUp[30],destination[30],driverName[30],vehicleType[30];
    double fare;
    RideHistory()
    {
        fare=0;
    }
    RideHistory(string pU,string d,string dN,string vT,double f){
        strcpy(pickUp, pU.c_str());
        strcpy(destination, d.c_str());
        strcpy(driverName, dN.c_str());
        strcpy(vehicleType, vT.c_str());
        fare = f;
    }
    void display()
    {
        cout<<"Source = "<<pickUp<<endl;
        cout<<"Destination = "<<destination<<endl;
        cout<<"Driver = "<<driverName<<endl;
        cout<<"Fare paid = Rs "<<fare<<endl;
    }
};

 
class Customer{
public:
    int custId,rideCount;
    static int custCount;
    static int logInFlag;
    vector<RideHistory *> rideHistory;
    string name;
    string emailId;
    string userName;
    string password;
    string phoneNo;
    double wallet;
    Customer(){
        rideCount=0;
        phoneNo="";
        userName="",name="",emailId="",password="";
        wallet=0;
        custCount++;
        custId = custCount;
    }
    void loadRideHistory(){
        Logs* L = L->getInstance();
        char buf[40];
        sprintf(buf,"ride_history_user%d.txt",custId);
        FILE *fp;
        fp = fopen(buf,"r");
        if(fp == NULL){
            L->write_log("load_ride_history", "FAILURE", "Ride history of user not loaded");
            return;
        }
        status = L->file_empty_check(buf);
        if(status == FILE_EMPTY_ERROR){
            fclose(fp);
            return;
        }
        while(!feof(fp)){
            RideHistory * newn=new RideHistory;
            cout<<newn->fare<<endl;
            fscanf(fp,"%s %s %s %s %0.2lf",newn->pickUp,newn->destination,newn->driverName,newn->vehicleType,&newn->fare);
            rideHistory.push_back(newn);
            rideCount++;
         }
         L->write_log("load_ride_history", "SUCCESS", "Ride history of user succefully loaded");
         fclose(fp);
    }
    void display(){
        cout<<"Customer Details are :\n";
        cout<<"UsernName:"<<userName<<endl;
        cout<<"Password:******"<<endl;
        cout<<"Customer Name ="<<name<<endl;
        cout<<"Customer PhoneNo = "<<phoneNo<<endl;
        cout<<"Customer Email = "<<emailId<<endl;
        cout<<"Wallet:"<<wallet<<endl;

    }
    int displayRideHistory(){
        if(rideCount != 0){ 
            for(int i=0;i<rideCount;i++)
                rideHistory[i]->display();
            return SUCCESS;
        }
        return FAILURE;
    }
    void updateRideHistory(string pickup,string destination,string name,string vehicle_type,double fare){
        RideHistory* newn = new RideHistory(pickup,destination,name,vehicle_type,fare);
        rideHistory.push_back(newn);
        rideCount++;
    }
    static void updateCustomer(){
        logInFlag = 1;
    }
};

int Customer::custCount=0;
int Customer::logInFlag=0;

vector<Customer *> customer;

class LogIn{
public:
    string userName;
    string password;
    string mobileNo;
    int state;
    LogIn()
    {
        userName = "";
        password = "";
        mobileNo = "";
    }
    virtual Customer* getData() {return NULL;}
    virtual char* generateotp() {return NULL;}
};

 
class SignIn:public LogIn
{
public:
    SignIn(){
        state = 0;
    }
    char* generateotp(){
        Logs *L = L->getInstance();
        int n = strlen(str);
        //Dynamic allocation of variable
        char* otp = new char[7];
        if(otp == NULL){
            cout << "Memory Allocation Failed\n";
            L->write_log("generateotp", "MEMORY_ALLOCATION_ERROR", "Memory allocation failed");
        }
        //Using rand() function for a random otp to be generated modulus the string length
        for(int i=0;i<6;i++){
            otp[i] = str[rand()%n];
        }
        L->write_log("generateotp", "SUCCESS", "OTP is successfully created");
        return otp;
    }
};


class SignUp:public LogIn{
public:
    SignUp(){
        state = 1;
    }
    Customer* getData(){
        char c;
        Customer *newn = new Customer;
        newn->phoneNo = mobileNo;
        cout << "Enter your details\n";
        cout << "UsernName:";
        cin >> newn->userName;
        cout << "Password:";
        getchar();
        while((c = getch()) != '\r'){
            newn->password.push_back(c);
            cout << "*";           
        }
        cout << "\nCustomer Name:";
        cin >> newn->name;
        cout << "Customer Email:";
        cin >> newn->emailId;
        cout << "Customer Wallet:";
        cin >> newn->wallet;
        char buf[40];
        sprintf(buf,"ride_history_user%d.txt",newn->custId);
        FILE *fp;
        fp = fopen(buf,"w");
        fclose(fp);
        return newn;
    }
    char* generateotp(){
        Logs *L = L->getInstance();
        int n = strlen(str);
        //Dynamic allocation of variable
        char* otp = new char[7];
        if(otp == NULL){
            cout << "Memory Allocation Failed\n";
            L->write_log("generateotp", "MEMORY_ALLOCATION_ERROR", "Memory allocation failed");
        }
        //Using rand() function for a random otp to be generated modulus the string length
        for(int i=0;i<6;i++){
            otp[i] = str[rand()%n];
        }
        L->write_log("generateotp", "SUCCESS", "OTP is successfully created");
        return otp;
    }
};


class Payment
{
public:
    double amount;
    void paymentOption(double &amt,double debitAmt)
    {
        if(debitAmt>amt)
            throw PaymentError("Insufficient balance in wallet");
        amt=amt-debitAmt;
        cout<<"Payment cleared\n";
    }
};

class Coupon
{
public:
    string code;
    int discount;
    Coupon(string c,int d)
    {
        code=c;
        discount=d;
    }
    void display()
    {
        cout<<"Coupon Code = "<<code<<endl;
        cout<<"Coupon discount = "<<discount<<endl;
    }

};
 

class OLA{
public:
    DriverCabLinkage driverCabLinkage;
    int index;
    int driverIndex;
    vector<Customer*> customer;
    OLA():index(0),driverIndex(0){
        Logs *L = L->getInstance();
        FILE *fp;
        char name[40],emailId[40],uN[40],pwd[40],pN[40];
        fp = fopen("users.txt","r");
        if(fp == NULL) {
             L->write_log("load", "FILE_OPEN_ERROR", "Unable to open the users file");
             cout << "Memory Allocation Failed\n";
        }
        while(!feof(fp)){
            Customer* newn = new Customer;
            //Transfer of string from secondary memory to primary memory
            fscanf(fp,"%s %s %s %s %s %lf",name,emailId,uN,pwd,pN,&newn->wallet);
            newn->name = name;
            newn->emailId = emailId;
            newn->userName=  uN;
            newn->password = pwd;
            newn->phoneNo = pN;
            customer.push_back(newn);
        }
        fclose(fp);
        char cL[40];
        // file_status = L->file_empty_check("drivers_count.txt");
        // if (file_status == 1006)
        //     L->
        fp = fopen("drivers.txt","r");
        if(fp == NULL){
            cout << "Failure";
            exit(-1);
        }
        while(!feof(fp)){
            DriverProfile* newn = new DriverProfile;
            fscanf(fp,"%s %lld %d %s",name,&newn->phoneNo,&newn->status,cL);
            newn->currentLocation = cL;
            newn->name = name;
            replace(newn->currentLocation);
            driverCabLinkage.drivers.push_back(newn);
            driverCabLinkage.count();
        }
        fclose(fp);
    }
    int loginValidation1(string mobile_no){
        Logs *L = L->getInstance();
        //Check for 10 digit mobile number
        if(mobile_no.length() == 10){
            for(int i=0;i<customer[i]->custCount;i++)
            {
                //check is user is existing in users list
                if(mobile_no == customer[i]->phoneNo){
                    index = i;
                    L->write_log("login_validation1", "SUCCESS", "Login Sucessful.");
                    return SUCCESS;
                }
            }
            L->write_log("login_validation1", "FAILURE", "Login UnSucessful/not signed up.");
            return FAILURE;
        }
        else{
            L->write_log("login_validation1", "FAILURE", "Login UnSucessful/Incorrect MOBILE number.");
            return FAILURE;  
        }
    }
    int loginValidation2(string email_id,string password){
        Logs *L = L->getInstance();
        for(int i=0;i<customer[i]->custCount;i++){
            //Traverse to the list and check for compatibility
            if((email_id == customer[i]->emailId) and (password == customer[i]->password)){
                index = i;
                L->write_log("login_validation1", "SUCCESS", "Login Sucessful.");
                return SUCCESS;
            }
        }
        L->write_log("login_validation1", "FAILURE", "Login UnSucessful/not signed up/Incorrect details.");
        return FAILURE;
    }
    int signUpValidation(string mobile_no){
        Logs *L = L->getInstance();
        //Check if the mobile number is 10 digits long(input has to be in digits)
        if(mobile_no.length() == 10){
            //Traverse the list to check for any dupliicates exist
            for(int i=0;i<customer[i]->custCount;i++){
                if(mobile_no == customer[i]->phoneNo){
                    L->write_log("signup_validation", "FAILURE", "Mobile NUMBER IS PRE-EXISTING");
                    return FAILURE;
                }
            }
            L->write_log("signup_validation", "SUCCESS", "Successfully signed up");
            return SUCCESS;
        }
        else{
            L->write_log("signup_validation", "FAILURE", "Mobile NUMBER IS Invalid");
            return FAILURE;
        }
    }
    Customer* addSubscriber(LogIn *LI){
        return LI->getData();
    }
    int loginSignUpPortal(LogIn* LI){
        flagl = 1;
        if(LI->state == 0){
            char c;
            while(flagl){
                cout << "\t************************\n";
                cout << "\t*     USER LOGIN       *\n";
                cout << "\t************************\n\n";
                cout << "Login using\n";
                cout << "1.Phone Number\n";
                cout << "2.Email and password\n";
                cout << "3.To go to main menu\n";
                cout << "Enter your choice:";
                cin >> choice3;
                switch(choice3){
                    case 1: cout << "\n\nENTER\n\n";
                            cout << "Mobile Number:";
                            cin >> LI->mobileNo;
                            status = loginValidation1(LI->mobileNo);
                            if(status != 1){
                                system("CLS");
                                cout << "Please enter a valid 10-digit mobile number / Not signed up yet.\n";
                                cout << "If not signed up yet,go to signup page.\n\n";
                                break;
                            }
                            else{
                                re_enter:
                                char* otp = new char[7];
                                otp = LI->generateotp();
                                cout << "(Mock)Enter otp sent to your mobile (Enter this " << otp <<" )";
                                cin >>temp;
                                if(!strcmp(temp,otp)){
                                    system("CLS");
                                    cout << "LOGIN SUCCESSFUL!!\n\n";
                                    LI->mobileNo.erase();
                                    Sleep(1000);
                                    customer[index]->loadRideHistory();
                                    flagl=0;
                                    system("CLS");
                                    return 1;
                                }
                                else{
                                    cout << "\nIncorrect OTP.\n\n\n";
                                    free(otp);
                                    goto re_enter;
                                }
                            }
                            break;
                    case 2:username:
                            cout << "\n\nENTER\n\n";
                            cout << "Email Id:";
                            cin >> LI->userName;
                            cout << "Password:";
                            getchar();
                            while((c = getch())!='\r'){
                                LI->password.push_back(c);
                                cout << "*";
                            }
                            status=loginValidation2(LI->userName,LI->password);
                            if(status!=1){
                                cout << "\nIncorrect EmailID/Password. (OR) Not signed up yet.\n";
                                cout << "If not signed up yet,go to signup page.\n\n";
                            }
                            else{
                                flagl=0;
                                cout << "LOGIN SUCCESSFUL!!\n\n";
                                LI->userName.erase();
                                LI->password.erase();
                                Sleep(1000);
                                customer[index]->loadRideHistory();
                                system("CLS");
                                return 1;
                            }
                            break;
                    case 3:flagl=0;
                           system("CLS");
                           return 0;
                           break;
                    default:system("CLS");
                            cout << "Invalid choice.Please input again!!\n\n";
                }
            }
        }
        else{ 
            while(flags){
               cout << "\t************************\n";
               cout << "\t*     USER SIGNUP      *\n";
               cout << "\t************************\n\n";
               cout << "SELECT\n";
               cout << "1.Enter your 10-digit mobile number\n";
               cout << "2.To go to main menu.\n";
               cout << "Enter your choice:";
               cin >> choice2;
               switch(choice2){
                  case 1:cout << "Mobile Number:";
                         cin >> LI->mobileNo;
                         status = signUpValidation(LI->mobileNo);
                         if(status != 1){
                            system("CLS");
                            cout << "Please enter a valid 10-digit mobile number or login if signed up already.\n\n";
                         }
                         else{
                            re_enter1:
                            char* otp = new char[7];
                            otp = LI->generateotp();
                            cout << "(Mock)Enter otp sent to your mobile (Enter this " << otp <<" )";
                            cin >> temp;
                            if(!strcmp(temp,otp)){
                               system("CLS");
                               cout << "SIGNUP SUCCESSFUL.\n\n";
                               Sleep(500);
                            }
                            else{
                               cout << "\nIncorrect OTP.\n\n\n";
                               free(otp);
                               goto re_enter1;
                            }
                            customer.push_back(addSubscriber(LI));
                            index = customer.size() - 1;
                            cout << "\n\nRedirecting to home page";
                            for(int i=0;i<4;i++){
                               cout << ".";
                               Sleep(500);
                            }
                            customer[index]->loadRideHistory();
                            return 1;
                         }
                         break;
                  case 2:flags=0;
                         system("CLS");
                         break;
                  default:system("CLS");
                          cout << "Invalid choice.Please input again!!\n\n";
               }
            }
          }
          return 0;
    }
    void printLocations(Computation C){
        C.displayLocations();
    }
    string locationValidation(string pick_dest,Computation C){
        int i,j,k,n,m;
        int count = 0;
    
        Logs* L = L->getInstance();
        //array of indexes with matches
        int* indexes = new int[C.locations_count];
        m = pick_dest.length();
    
        //Check for matching string in the given locations
        for(i=0;i<C.locations_count;i++){
            n = C.locations[i].length();
            for(j=0;j<=(n-m);j++){
                k = 0;
    
                //Cotinue the loop till match is found
                while((k<m) && (pick_dest[k] == C.locations[i][j+k])){
                    k = k+1;
                }
    
                //If match is found load it to the indexes array 
                if(k == m){
                    indexes[count] = i;
                    count++;
                    break;
                }
            }
        }
        
        //No matching sub-strings found
        if(count==0){
            cout << "No matching locations found!! Re-enter the pickup location.\n";
    
            L->write_log("location_validation", "FAILURE", "No matching locations found.");
            return "";
        }
        //If there is only one match, ask for confirmation
        else if(count == 1){
            re_enter:
            cout << "Pickup Location chosen is:" << C.locations[indexes[0]] << endl;
            cout << "Press 1 to confirm\n";
            cout << "Press 2 to Re-enter\n";
            cout << "Enter your choice:";
            cin >> choice5;
            switch(choice5){
                case 1:pick_dest = C.locations[indexes[0]];
                       L->write_log("location_validation", "SUCCESS", "matching locations found and approved.");
                       return pick_dest;
                       break;
                case 2:L->write_log("location_validation", "SUCCESS", "matching locations found but not approved.");
                       return "";
                       break;
                default:cout << "Invalid choice please re-enter!!\n";
                        goto re_enter;
            }
        }
        //Multiple matches, display the strings and ask for confirmation
        else{
            re_enter1:
            cout << "Possible Locations to choose from\n";
            for(i=0;i<count;i++){
                cout << i+1<<"."<<C.locations[indexes[i]]<<endl;
            }
            cout << "\nPress 1 to choose from above locations\n";
            cout << "Press 2 to Re-enter\n";
            cout << "Enter your choice:";
            cin >> choice5;
            switch(choice5){
                case 1:re_enter2:
                       cout << "Enter your location choice:";
                       cin >> ans;
                       if(ans>count){
                           cout << "Incorrect choice!! Re-enter\n";
                           goto re_enter2;
                       }
                       pick_dest = C.locations[indexes[ans-1]];
                       L->write_log("location_validation", "SUCCESS", "matching locations found and approved.");
                       return pick_dest;
                       break;
                case 2:L->write_log("location_validation", "SUCCESS", "matching locations found but not approved.");
                       return "";
                       break;
                default:cout << "Invalid choice please re-enter!!\n";
                        goto re_enter1;
            }
        }
    }
    int selectCouponCode(Coupon C[],string coupon_temp){
        Logs *L = L->getInstance();
         //Traverse through coupons list and find the apporpriate coupon
         for(int i=0;i<5;i++){
             if(coupon_temp == C[i].code){
                 L->write_log("search_coupon", "SUCCESS", "Coupon code found.");
                 return C[i].discount;
             }
         }
         throw InvalidCoupon("Coupon Unavailable");
         L->write_log("search_coupon", "FAILURE", "Coupon code NOT found.");
         return FAILURE;
    }
    void payment(Payment P,double &amt,double debitamt){
        P.paymentOption(amt,debitamt);
    }
    void bookCabs(Computation C1,Computation C2,Coupon C[]){
         re_enter2:
         string pickup,destination;
         cout << "Enter the pickup location(Case-sensitive):";
         getchar();
         getline(cin,pickup);
         pickup = locationValidation(pickup,C1);
         if(pickup == ""){
           goto re_enter2;
         }
         re_enter3:
         cout << "\nEnter the destination location(Case-sensitive):";
         getchar();
         getline(cin,destination);
         destination = locationValidation(destination,C1);
         if(destination == ""){
           goto re_enter3;
         }
         driverCabLinkage.displayCabs();
         cout << "\nEnter vehicle type:";
         cin >> vehicle_type;
         C1.driverETA();
         float min=MAX;
         index1 = C1.searchLocation(pickup);
         for(int i=0;i<driverCabLinkage.driverCount;i++)
         {
             index2 = C1.searchLocation(driverCabLinkage.drivers[i]->currentLocation);
             if(driverCabLinkage.drivers[i]->vehicleType == vehicle_type and driverCabLinkage.drivers[i]->status == false){
                if(min>C1.timeEstimate[index1][index2]){
                    min=C1.timeEstimate[index1][index2];
                    driverIndex = i;
                 }
             }
         }
         cout << driverCabLinkage.drivers[driverIndex]->name <<" will arrive in "<<min<<" minutes\n";
         cout << "Driver Details\n";
         driverCabLinkage.drivers[driverIndex]->display();
         cout << "Cab Details\n";
         driverCabLinkage.cabs[driverIndex]->display();
         cout << "Press 0 TO CONTINUE\n";
         cin >> choice6;
         if(choice6 != 0){
             return;
         }
         cout << "Journey starts\n\n";
         Sleep(200);
         double amt;
         double cost = C2.shotestPath(pickup,destination);
         cost = cost*driverCabLinkage.cabs[driverIndex]->fare;
         cout << "\n The Total Cost is " << cost << "\n";
         re__enter:
         cout << "Do you have coupon code?\n";
         cout << "1.Yes\n2.No\n";
         cout << "Enter your choice:";
         cin >> code;
         if(code== 1){
             for(int i=0;i<5;i++)
                C[i].display();
            cout << "Enter coupon code:";
            cin >> coupon_temp;
            dis = selectCouponCode(C,coupon_temp);
            cost = cost - dis;
            amt_enter:
            cout << "Enter "<< cost <<" amount:";
            cin >> amt;
            if(amt==cost){
               Payment P;
               payment(P,customer[index]->wallet,amt);
               customer[index]->updateRideHistory(pickup,destination,driverCabLinkage.drivers[driverIndex]->name,
               driverCabLinkage.drivers[driverIndex]->vehicleType,cost);
               driverCabLinkage.drivers[driverIndex]->changeCurrentLocation(destination);
               system("CLS");
            }
            else
              goto amt_enter;
         }
         else if(code == 2){
            cout << "Enter Rs " << cost << endl;
            cin >> amt;
            if(amt == cost){
               Payment P;
               payment(P,customer[index]->wallet,amt);
               customer[index]->updateRideHistory(pickup,destination,driverCabLinkage.drivers[driverIndex]->name,
               driverCabLinkage.drivers[driverIndex]->vehicleType,cost);
               driverCabLinkage.drivers[driverIndex]->changeCurrentLocation(destination);
               system("CLS");
           }
         }
         else
            goto re__enter;
    }
    
    int logout(){
        FILE* fp;
        Logs* L = L->getInstance();
        char buf[40];
        sprintf(buf,"ride_history_user%d.txt",customer[index]->custId);
        fp = fopen(buf,"w");
        if(fp == NULL){
            L->write_log("logout", "FAILURE", "Ride history of user NOT succefully re-loaded");
            return FAILURE;
        }
        for(int i=0;i<customer[index]->rideCount;i++){
            fprintf(fp,"%s %s %s %s %0.2lf\n",customer[index]->rideHistory[i]->pickUp,customer[index]->rideHistory[i]->destination,customer[index]->rideHistory[i]->driverName,customer[index]->rideHistory[i]->vehicleType,customer[index]->rideHistory[i]->fare);
        }
        L->write_log("logout", "SUCCESS", "Ride history of user succefully re-loaded");
        fclose(fp);
        return SUCCESS;
    }
    int exitDump(){
        Logs *L = L->getInstance();
        FILE *fp;
        fp = fopen("users.txt","w");
        if(fp == NULL) {
             L->write_log("exitDump", "FILE_OPEN_ERROR", "Unable to open the users file");
             cout << "Memory Allocation Failed\n";
        }
        for(int i=0;i<customer.size();i++){
            //Transfer of string from secondary memory to primary memory
            fprintf(fp,"%s %s %s %s %s %lf\n",customer[i]->name.c_str(),customer[i]->emailId.c_str(),customer[i]->userName.c_str(),customer[i]->password.c_str(),customer[i]->phoneNo.c_str(),customer[i]->wallet);
        }
        L->write_log("exitDump", "SUCCESS", "Users List successfully transferred to secondary memory");
        fclose(fp);
        return SUCCESS;
    }
}; 