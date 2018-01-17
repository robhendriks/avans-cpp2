#ifndef turn_h
#define turn_h

#include <string>
#include <vector>

namespace machiavelli
{
    class turn_manager;
    class turn
    {
        turn_manager& m_context;
        std::string m_name;
        std::vector<std::string> m_command_names; 
    public:
        turn(turn_manager& context, const std::string& name) : m_context{context}, m_name{name} {}
        
        void add_commands();
        void remove_commands();
        virtual void register_commands() {}
        
        virtual void on_enter();
        virtual void on_leave();
        
        turn_manager& get_context() const { return m_context; }
        std::string get_name() const { return m_name; }
    };
}

#endif
