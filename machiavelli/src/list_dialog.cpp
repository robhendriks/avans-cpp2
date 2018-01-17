#include "list_dialog.hpp"

namespace machiavelli
{
    const uint8_t list_dialog::item_first    = 1 << 0;
    const uint8_t list_dialog::item_last     = 1 << 1;
    const uint8_t list_dialog::item_odd      = 1 << 2;
    const uint8_t list_dialog::item_even     = 1 << 3;
    
    void list_dialog::fill(std::initializer_list<string_utils::string_convertible> il)
    {
        for (auto& item : il) {
            m_items.push_back(item.to_string());
        }
    }
    
    void list_dialog::format(std::stringstream& ss) const
    {
        dialog::format(ss);
        format_items(ss);
    }
    
    void list_dialog::format_items(std::stringstream& ss) const
    {
        size_t i = 0, size = m_items.size();
     
        ss << size << " item(s)" << ESCAPE;
        
        for (auto& item : m_items) {
            uint8_t flags = 0;
            
            if (i == 0) { flags |= item_first; }
            if (i == size - 1) { flags |= item_last; }
            if (i % 2) { flags |= item_odd; }
            else { flags |= item_even; }
            
            format_item(ss, item, i, flags);
            ++i;
        }
    }
    
    void list_dialog::format_item(std::stringstream& ss, const std::string& item, size_t index, uint8_t flags) const
    {
//        if (flags & item_even) {
//            ss << "\e[38;5;66m";
//        } else {
//            ss << "\e[38;5;67m";
//        }
        ss << "\e[2m[" << index << "] \e[0m" << item << "\e[0m" << ESCAPE;
    }
}
