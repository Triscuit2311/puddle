#pragma once
#include <functional>

/**
 * @class puddle
 * @brief A template class for obfuscating a value within a random memory buffer.
 *
 * The puddle class provides methods to set and get values in a way that obfuscates the actual value stored.
 * It also allows performing equality and relational operations with lambdas for additional flexibility and obfuscation.
 *
 * @tparam T The data type of the value to be obfuscated.
 */
template<typename T>
class puddle{
    static constexpr unsigned int buff_sz_factor_ = 100;
    char buff_[sizeof(T) * buff_sz_factor_];

    public:

    /**
     * @brief Constructor that initializes the puddle with an initial value.
     * 
     * @param initial The initial value to store in the puddle.
     */
    puddle(T initial){
        this->set(initial);
    }

    /**
     * @brief Retrieves the obfuscated value from the puddle.
     * 
     * @param out Reference to a variable where the retrieved value will be stored.
     */
    void get(T& out){
        [&](){
            unsigned int buff__offset = (unsigned int)(((uint64_t)this) % ((sizeof(T) * buff_sz_factor_) - 0x01 - sizeof(T)));
            // set out bytes from val area of buff_
            for(unsigned int i = 0; i < sizeof(T); i++){
                *(((char*)&out) + i) = buff_[buff__offset + i] ^ ((buff__offset + (i + buff__offset)) % 0xff);
            }
        }();
    }

    /**
     * @brief Sets a new value in the puddle, obfuscating it in the process.
     * 
     * @param val The value to be obfuscated and stored in the puddle.
     */
    void set(T val){
        [&](){
            unsigned int buff__offset = (unsigned int)(((uint64_t)this) % ((sizeof(T) * buff_sz_factor_) - 0x01 - sizeof(T)));

            // set all new bytes in buff_, set value bytes from input
            for(int i = 0; i < sizeof(T) * buff_sz_factor_; i++){
                if(i >= buff__offset && i < buff__offset + sizeof(T)){
                    buff_[i] = *(((char*)&val) + (i-buff__offset)) ^ ((buff__offset + i) % 0xff);
                    continue;
                }
                buff_[i] = rand() % (sizeof(T) * buff_sz_factor_);
            }
        }();
    }

    /**
     * @brief Compares the current value in the puddle with another value for equality.
     * 
     * @param rhs The value to compare with.
     * @param on_true Lambda function to execute if the values are equal.
     * @param on_false Lambda function to execute if the values are not equal (optional).
     */
    void eq(T rhs, std::function<void(T& val)> on_true, std::function<void(T& val)> on_false = [](T& v){}){
        [&](){
            T v;
            get(v);
            if(rhs == v){
                on_true(v);
                return;
            }
            on_false(v);
        }();
    }

    /**
     * @brief Compares the current value in the puddle with another value for inequality.
     * 
     * @param rhs The value to compare with.
     * @param on_true Lambda function to execute if the values are not equal.
     * @param on_false Lambda function to execute if the values are equal (optional).
     */
    void neq(T rhs, std::function<void(T& val)> on_true, std::function<void(T& val)> on_false = [](T& v){}){
        [&](){
            T v;
            get(v);
            if(rhs != v){
                on_true(v);
                return;
            }
            on_false(v);
        }();
    }

    /**
     * @brief Checks if the current value in the puddle is greater than another value.
     * 
     * @param rhs The value to compare with.
     * @param on_true Lambda function to execute if the current value is greater.
     * @param on_false Lambda function to execute otherwise (optional).
     */
    void gt(T rhs, std::function<void(T& val)> on_true, std::function<void(T& val)> on_false = [](T& v){}){
        [&](){
            T v;
            get(v);
            if(v > rhs){
                on_true(v);
                return;
            }
            on_false(v);
        }();
    }

    /**
     * @brief Checks if the current value in the puddle is greater than or equal to another value.
     * 
     * @param rhs The value to compare with.
     * @param on_true Lambda function to execute if the current value is greater or equal.
     * @param on_false Lambda function to execute otherwise (optional).
     */
    void gte(T rhs, std::function<void(T& val)> on_true, std::function<void(T& val)> on_false = [](T& v){}){
        [&](){
            T v;
            get(v);
            if(v >= rhs){
                on_true(v);
                return;
            }
            on_false(v);
        }();
    }

    /**
     * @brief Checks if the current value in the puddle is less than another value.
     * 
     * @param rhs The value to compare with.
     * @param on_true Lambda function to execute if the current value is less.
     * @param on_false Lambda function to execute otherwise (optional).
     */
    void lt(T rhs, std::function<void(T& val)> on_true, std::function<void(T& val)> on_false = [](T& v){}){
        [&](){
            T v;
            get(v);
            if(v < rhs){
                on_true(v);
                return;
            }
            on_false(v);
        }();
    }
    
    /**
     * @brief Checks if the current value in the puddle is less than or equal to another value.
     * 
     * @param rhs The value to compare with.
     * @param on_true Lambda function to execute if the current value is less or equal.
     * @param on_false Lambda function to execute otherwise (optional).
     */
    void lte(T rhs, std::function<void(T& val)> on_true, std::function<void(T& val)> on_false = [](T& v){}){
        [&](){
            T v;
            get(v);
            if(v < rhs){
                on_true(v);
                return;
            }
            on_false(v);
        }();
    }

};
