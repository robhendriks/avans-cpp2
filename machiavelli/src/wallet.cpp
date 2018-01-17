#include "wallet.hpp"

namespace machiavelli
{
    wallet& wallet::add(int amount)
    {
        set_balance(m_balance + amount);
        m_income += amount; // stats
        
        return *this;
    }
    
    wallet& wallet::remove(int amount)
    {
        int new_balance = m_balance - amount;
        if (new_balance < 0) {
            throw wallet_error{"insufficient funds"};
        }
        
        set_balance(new_balance);
        m_expenses += amount; // stats
        
        return *this;
    }
    
    wallet& wallet::transfer(int amount, wallet& other)
    {
        remove(amount);
        other.add(amount);
        return *this;
    }
    
    wallet& wallet::transfer(wallet& other)
    {
        return transfer(get_balance(), other);
    }
    
    wallet& wallet::reset()
    {
        m_income = m_expenses = m_balance = 0;
        return *this;
    }
    
    std::string wallet::to_string() const
    {
        return "{balance=" + std::to_string(m_balance) + '}';
    }
}
