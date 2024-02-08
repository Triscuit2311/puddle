#include <cstdio>

#include "puddle.hpp"


class puddle_tests{

    struct test_struct{
        int i32;
        bool b;
        float f32;
        char c;

        test_struct(){
            i32 = 1234;
            b = true;
            f32 = 123.456;
            c = 'Q';
        }

        test_struct(int _i32, bool _b, float _f32, char _c) 
            : i32(_i32), b(_b), f32(_f32), c(_c) {}

        bool operator == (const test_struct& rhs) const {
            return i32 == rhs.i32 && b == rhs.b && c == rhs.c && std::abs(f32 - rhs.f32) < 0.00001f;
        }

    };

    bool run_struct_tests(){

        const test_struct ts_a(456, true, 999.999f, 'P');

        bool test_flag =  true;

        puddle<test_struct> p(test_struct{});

        {
            bool flag = true;
            test_struct x;
            p.eq(x, [&flag](test_struct v){flag = true;});
            p.eq(ts_a, [&flag](test_struct v){flag = false;});
            p.eq(x, [&flag](test_struct v){flag = true;},[&flag](test_struct v){flag = false;});
            p.eq(ts_a, [&flag](test_struct v){flag = false;},[&flag](test_struct v){flag = true;});
            printf("Struct Tests: %s\n", flag ? "Passed" : "Failed");
            test_flag = test_flag && flag;
        }

        return test_flag;
    }

    bool test_int(){

        bool test_flag =  true;

        puddle<int> p(0);
        
        {
            int n = 1;
            p.get(n);
            test_flag = test_flag && n == 0;
            printf("Get Test: %s\n", n == 0 ? "Passed" : "Failed");
        }

        {
            int n = 123;
            p.set(n);
            p.get(n);
            test_flag = test_flag && n == 123;
            printf("Set Test: %s\n", n == 123 ? "Passed" : "Failed");
        }

        {
            bool flag = true;
            p.eq(123, [&flag](int v){flag = true;});
            p.eq(999, [&flag](int v){flag = false;});
            p.eq(123, [&flag](int v){flag = true;},[&flag](int v){flag = false;});
            p.eq(999, [&flag](int v){flag = false;},[&flag](int v){flag = true;});
            printf("Eq Tests: %s\n", flag ? "Passed" : "Failed");
            test_flag = test_flag && flag;
        }


        {
            bool flag = true;
            p.neq(123, [&flag](int v){flag = false;});
            p.neq(999, [&flag](int v){flag = true;});
            p.neq(123, [&flag](int v){flag = false;},[&flag](int v){flag = true;});
            p.neq(999, [&flag](int v){flag = true;},[&flag](int v){flag = false;});
            printf("Neq Tests: %s\n", flag ? "Passed" : "Failed");
            test_flag = test_flag && flag;

        }
        
        {
            bool flag = true;
            p.gt(100, [&flag](int v){flag = true;});
            p.gt(200, [&flag](int v){flag = false;});
            p.gt(100, [&flag](int v){flag = true;},[&flag](int v){flag = false;});
            p.gt(200, [&flag](int v){flag = false;},[&flag](int v){flag = true;});
            printf("Gt Tests: %s\n", flag ? "Passed" : "Failed");
            test_flag = test_flag && flag;
        }
        
        {
            bool flag = true;
            p.lt(100, [&flag](int v){flag = false;});
            p.lt(200, [&flag](int v){flag = true;});
            p.lt(100, [&flag](int v){flag = false;},[&flag](int v){flag = true;});
            p.lt(200, [&flag](int v){flag = true;},[&flag](int v){flag = false;});
            printf("Lt Tests: %s\n", flag ? "Passed" : "Failed");
            test_flag = test_flag && flag;
        }

        {
            bool flag = true;
            p.gte(100, [&flag](int v){flag = true;});
            p.gte(200, [&flag](int v){flag = false;});
            p.gte(100, [&flag](int v){flag = true;},[&flag](int v){flag = false;});
            p.gte(200, [&flag](int v){flag = false;},[&flag](int v){flag = true;});
            printf("Gte Tests: %s\n", flag ? "Passed" : "Failed");
            test_flag = test_flag && flag;
        }
        
        {
            bool flag = true;
            p.lte(100, [&flag](int v){flag = false;});
            p.lte(200, [&flag](int v){flag = true;});
            p.lte(100, [&flag](int v){flag = false;},[&flag](int v){flag = true;});
            p.lte(200, [&flag](int v){flag = true;},[&flag](int v){flag = false;});
            printf("Lte Tests: %s\n", flag ? "Passed" : "Failed");
            test_flag = test_flag && flag;
        }

        return test_flag;
    }

public:
    bool run_tests(){

       return test_int() && run_struct_tests();
    }


};



int main(){

    puddle_tests p;
    p.run_tests();

    return 0;
}
