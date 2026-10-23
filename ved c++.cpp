// Online C++ compiler (editor)
// Write and run C++ online using this editor.

#include <iostream>
using namespace std;

class Timeconvertor
{
    public:

    void secondtotime()
    {
        int totalsecond;
        int hours,minutes,seconds;
        
        cout <<"Enter total seconds:";
        cin >> totalsecond;

        hours= totalsecond/3600;
        minutes= (totalsecond%3600)/60;
        seconds= totalsecond%60;

        cout << "HH:MM:SS=>" << hours <<":" << minutes << ":" << seconds << endl;
    }
    void timetosecond()
    {
        int hours,minutes,seconds;

        cout << "Enter hours:";
        cin >> hours;
        cout << "Enter minutes:";
        cin >>  minutes;
        cout << "Enter seconds:";
        cin >> seconds;

        int totalseconds=(hours * 3600)+(minutes * 60)+seconds;
        cout << "total seconds:" << totalseconds << endl;
    }
};
int main() {
    Timeconvertor obj;
    obj.secondtotime();
    obj.timetosecond();
    return 0;
}

























#include <iostream>
using namespace std;

class Parent
{
public:
    int publicData;

protected:
    int protectedData;

private:
    int privateData;
};

class PublicChild : public Parent
{
public:
    void display()
    {
        publicData = 10;       // Accessible
        protectedData = 20;    // Accessible

        cout << publicData << endl;
        cout << protectedData << endl;

        // privateData = 30;   // Error
    }
};

class ProtectedChild : protected Parent
{
public:
    void display()
    {
        publicData = 10;       // Now protected
        protectedData = 20;    // Remains protected

        cout << publicData << endl;
        cout << protectedData << endl;
    }
};

class PrivateChild : private Parent
{
public:
    void display()
    {
        publicData = 10;       // Now private in this class
        protectedData = 20;    // Now private in this class

        cout << publicData << endl;
        cout << protectedData << endl;
    }
};

int main()
{
    PublicChild p;
    p.publicData = 100;   // Allowed
    p.display();

    ProtectedChild q;
    q.display();
    // q.publicData = 100; // Error

    PrivateChild r;
    r.display();
    // r.publicData = 100; // Error

    return 0;