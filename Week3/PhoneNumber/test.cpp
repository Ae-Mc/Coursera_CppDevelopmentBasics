#include "phone_number.h"
#include <stdexcept>

class Tester {
public:
    void test(string number) {
        try {
            auto p = PhoneNumber(number);
            if(p.GetInternationalNumber() != number) {
                throw invalid_argument(p.GetInternationalNumber() + " != " + number);
            }
            printf("\"%s\" Ok\n", number.c_str());
        } catch(invalid_argument e) {
            printf("\"%s\" failed: '%s'\n", number.c_str(), e.what());
            failed++;
        }
    }

    int failed = 0;
};

int main() {
    Tester t;
    t.test("+7-952-277-93-03");
    t.test("+7-952-2779303");
    t.test("+7-9522779303");
    t.test("1-2-333");
    t.test("+7-1233");
    printf("Failed %d tests\n", t.failed);
    return 0;
}
