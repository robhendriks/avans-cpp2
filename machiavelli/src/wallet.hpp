#ifndef wallet_h
#define wallet_h

#include "string_utils.hpp"
#include <stdexcept>

namespace machiavelli
{
    class wallet_error : public std::runtime_error
    {
    public:
        wallet_error(const std::string& msg) : std::runtime_error{msg} {}
    };
    
    class wallet : public string_utils::string_convertible
    {
        int m_balance;
        int m_income;
        int m_expenses;
    public:
        wallet() : wallet{0} {}
        wallet(int balance) : m_balance{balance}, m_income{0}, m_expenses{0} {}
        wallet(const wallet& w) : wallet{w.m_balance} {}
        
        wallet& add(int amount);
        wallet& remove(int amount);
        wallet& transfer(int amount, wallet& other);
        wallet& transfer(wallet& other);
        wallet& reset();
        
        wallet& operator=(const wallet& other)
        {
            if (this != &other) {
                m_balance = other.m_balance;
            }
            return *this;
        }
        
        std::string to_string() const override;
        
        int get_balance() const { return m_balance; }
        void set_balance(int balance) { m_balance = std::abs(balance); }
        int get_income() const { return m_income; }
        int get_expenses() const { return m_expenses; }
    };
}

#endif
