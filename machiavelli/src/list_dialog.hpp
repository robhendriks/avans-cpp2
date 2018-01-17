#ifndef list_dialog_hpp
#define list_dialog_hpp

#include "dialog.hpp"

namespace machiavelli
{
    class list_dialog : public dialog
    {
        std::vector<std::string> m_items;
    protected:
        static const uint8_t item_first, item_last, item_odd, item_even;
        
        virtual void fill(std::initializer_list<string_utils::string_convertible> il);
        virtual void format(std::stringstream& ss) const override;
        virtual void format_items(std::stringstream& ss) const;
        virtual void format_item(std::stringstream& ss, const std::string& item, size_t index, uint8_t flags) const;
        
    public:
        list_dialog() : dialog{} {}
        list_dialog(const std::vector<std::string>& items) : m_items{items} {}
        list_dialog(std::initializer_list<std::string> il) : dialog{}, m_items{il} {}
        list_dialog(std::initializer_list<string_utils::string_convertible> il) : dialog{} { fill(il); }
        
        std::vector<std::string>& get_items() { return m_items; }
        const std::vector<std::string>& get_items() const { return m_items; }
    };
}

#endif
