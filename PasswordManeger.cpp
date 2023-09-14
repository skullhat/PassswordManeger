#include <iostream>
#include <string>
#include <fstream>

class Password{
    
    private:
        
        int passwordSize;
    public:
        std::string passwordString;
        int passwordStrengthRate;

        Password(): passwordSize(0), passwordStrengthRate(0){}

    Password(std::string passwordString): passwordString(passwordString){
            this->passwordSize = passwordString.size();
            this->passwordStrengthRate = this->getPasswordStrengthRate();
            
    }
    Password(std::string passwordString, bool feedback): passwordString(passwordString){
        this->passwordSize = passwordString.size();
        this->passwordStrengthRate = this->getPasswordStrengthRate();
        if (feedback)
            this->getFeedback();
    }

    void inti(std::string pass){
        this->passwordString = pass;
        this->passwordSize = passwordString.size();
        this->passwordStrengthRate = this->getPasswordStrengthRate();
    }
    bool isLong() const{
        return this->passwordSize >= 8;
    }

    bool hasDigits() const{
        int count = 0;
        for (int i = 0; i< this->passwordSize ; i++){
            if(isdigit(passwordString[i]))
                count++;
        }
        return (count > 0);
    }

    bool hasUpperAndLowerCase() const{
        int countC = 0;
        int countL = 0;
        for (int i = 0; i< this->passwordSize ; i++){
            if(isupper(passwordString[i]) )
                countC++;
            else if(islower(passwordString[i]))
                countL++;
        }
        return (countC > 0) && (countL > 0);
    }

    bool hasSpcialChars() const{
        int count = 0;
        for (int i = 0; i< this->passwordSize ; i++){
            if(!std::isalpha(this->passwordString[i]) && !std::isdigit(this->passwordString[i]) && this->passwordString[i]!='_')
                count++;
            
        }
        return (count > 0);
    }

    bool isCommon() const{
        std::ifstream common("topPasswords.txt");
        
        if (common.is_open()) {
            std::string ps;
            while (std::getline(common, ps)) {
                if (ps.compare(this->passwordString) == 0) {
                    //std::cout << ps << std::endl;
                    return true;
                }
            }
            common.close();
        }
        
        return false;
    }

    int getPasswordStrengthRate(){
        this->passwordStrengthRate = 0;
        if(this->isLong())
            this->passwordStrengthRate += 25;
        if (this-> hasDigits())
            this->passwordStrengthRate += 25;
        if (this->hasUpperAndLowerCase())
            this->passwordStrengthRate += 25;
        if (this->hasSpcialChars())
            this->passwordStrengthRate += 25;
        if (this->isCommon())
            this->passwordStrengthRate += 25;
        return this->passwordStrengthRate;
    }
    void getFeedback(){
        std::cout << std::endl << "Contain 8 charectors at least: " ;

        this->isLong() ? std::cout << " Yes " << std::endl: std::cout << " No " << std::endl;

        std::cout << "Has one digit at least : ";

        (this->hasDigits()) ? std::cout << " Yes " << std::endl: std::cout << " No " << std::endl;
        
        std::cout << "Has uppercase and lowercase letters: ";

        (this->hasUpperAndLowerCase()) ? std::cout << " Yes " << std::endl:std::cout << " No "<< std::endl;

        std::cout << "Has one spcial charector at least: ";

        (this->hasSpcialChars()) ? std::cout << " Yes " << std::endl: std::cout << " No "<< std::endl;

        std::cout << "Is a common password: ";

        (this->isCommon()) ? std::cout << " Yes " << std::endl: std::cout << " No "<< std::endl;

    
    }
};

class PassowrdGenerator: Password{
    private:
        int passwordLength;
        std::string genPass;
    int genRandomInRange(int min , int max ){
            static bool first = true;
            if (first) 
            {  
                srand( time(NULL) ); //seeding for the first time only!
                first = false;
            }
            return  min + std::rand() % (( max + 1 ) - min);
        }
        void genUpperCaseString(){
            std::string uppers;
            for (int i = 0; i< this->passwordLength; i++){
                uppers.push_back((char)genRandomInRange('A','Z'));
            }
            //std::cout << uppers;
            this->genPass = uppers;
        }
        void addLowerCase(){
            int random = genRandomInRange(0,this->passwordLength-3);
            for (int i = 0; i< random; i++){
                this->genPass[genRandomInRange(0,this->passwordLength)]= (char)genRandomInRange('a','z');
            }
            //std::cout << "\n"<< this->genPass;
        }
        void addSpcialChars(){
            int random = genRandomInRange(1,3);
            for (int i = 0; i< this->passwordLength/6; i++){
                switch(random){
                    case 1:
                        this->genPass[genRandomInRange(0,this->passwordLength)]= (char)genRandomInRange(33,43);
                        random = genRandomInRange(1,4) ;
                        continue;
                    case 2:
                        this->genPass[genRandomInRange(0,this->passwordLength)]= (char)genRandomInRange(91,95);
                        random = genRandomInRange(1,4);
                        continue;
                    case 3:
                        this->genPass[genRandomInRange(0,this->passwordLength)]= (char)genRandomInRange(58,64);
                        random = genRandomInRange(1,4);
                        continue;
                }   
            }
            
            //std::cout << "\n"<< this->genPass;
        }
    public:
        PassowrdGenerator(): passwordLength(genRandomInRange(8, 16)) {
            this->genUpperCaseString();
            this->addLowerCase();
            this->addSpcialChars();
        }
        PassowrdGenerator(int passwordLength ): passwordLength(passwordLength) {
            this->genUpperCaseString();
            this->addLowerCase();
            this->addSpcialChars();
        }
        std::string getPassowrd(){
            return genPass;
        }

        
};

void printMenu() {
    std::cout << std::endl <<  "---------- Password Checker CLI ----------" << std::endl;
    std::cout << "1. Generate Strong Password" << std::endl;
    std::cout << "2. Check If A Password Is Strong" << std::endl;
    std::cout << "3. Exit from the Program" << std::endl;
    std::cout << "Enter your choice: ";
}

int main(){
    printMenu();
    int choise;
    int passGenMenueChoise;
    int passFeedbackChoise;

    std::string inputPassword;
    Password withoutFeedback(inputPassword);

    std::cin >> choise;

    while(choise !=3){

        switch(choise){
            case 1:
                std::cout << std::endl << "---------- Passowrd Genertion Options ----------" << std::endl;
                std::cout << "1. Create Random Strong Password" << std::endl;
                std::cout << "2. Create a Spacific Length Passowrd" << std::endl;
                std::cout << "Enter your choice: ";
                
                std::cin >> passGenMenueChoise;

                if (passGenMenueChoise == 1 ){
                    PassowrdGenerator ps;
                    std::cout << "Your New Passowrd is: " << ps.getPassowrd();
                }
                else if (passGenMenueChoise ==2){
                    int length;
                    std::cout << "Enter the Passowrd Length: ";
                    std::cin >> length;
                    PassowrdGenerator ps(length);
                    std::cout << "Your New Passowrd is: " << ps.getPassowrd();
                }
                else{
                    std::cout << "Unknown Choise!";
                }

                
            break;

            case 2:
                std::cout << "---------- Check Password Complexity ----------" << std::endl;
                std::cout << "Enter the Passowrd: ";
                std::cin >> inputPassword;
                withoutFeedback.inti(inputPassword);
                std::cout << "Passowrd Rating: " << withoutFeedback.getPasswordStrengthRate() << "%" << std::endl; 
                std::cout << "Do you want the feedback of your password ?" << std::endl << "(Enter 1 to view it): ";
                std::cin >> passFeedbackChoise;
                if (passFeedbackChoise)
                    withoutFeedback.getFeedback();
            break;

            case 3:
            break;

            default:
            std::cout << "Unknown Choise!";
        }

        printMenu();
        std::cin >> choise;
    }
    return 0;
}
