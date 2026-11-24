
#pragma once

#include <functional>
#include <iostream>

#include "button.hpp"

/// @brief Un élément d'un radiobutton, stocke le bouton et la valeur qui lui est attribuée.
/// @tparam ButtonT doit hériter de (ou être un) BareButton, type de bouton
/// @tparam ValueT Valeur stockée dans l'élément
template <typename ButtonT, typename ValueT>
struct RBTElm {
    ButtonT button;
    ValueT value;
};

/// @brief self explanatory
/// @tparam ButtonT doit hériter de (ou être un) BareButton, type de bouton
/// @tparam ValueT Le type de valeur a attribuer à chaque radiobutton
/// @tparam nb_button number of button
template <std::size_t nb_button, typename ButtonT, typename ValueT>
class RadioButtonG {
private:
    int curr_value_index;
    using RBTElm = ::RBTElm<ButtonT, ValueT>;

    RBTElm elements[nb_button];

    using FonctionT = std::function<void(const ValueT&)>;
    FonctionT on_update;

public:
    inline RBTElm* begin() { return &elements[0]; }
    inline RBTElm* end()   { return &elements[nb_button]; }

    inline const RBTElm* begin() const { return &elements[0]; }
    inline const RBTElm* end()   const { return &elements[nb_button]; }

    inline const ValueT& get_selected() const { return elements[curr_value_index].value; }
    inline std::size_t size() { return nb_button; }
    inline RBTElm& operator[](const unsigned int& index)
    {
        if(index < nb_button) return elements[index];
        else {
            std::cerr << "IndexError: Tentative d'accès à un bouton qui n'existe pas dans un radiobutton: " << index << std::endl;
            exit(0);
        }
    };

    RadioButtonG(const int& index_selected_default = 0): curr_value_index(index_selected_default), elements() {
        for(unsigned int i = 0U; i < nb_button; i++){
            elements[i].button.set_on_click([this, i](){
                curr_value_index = i;
                on_update(get_selected());
            });
        }
    }

    inline void set_on_update(const FonctionT& f) { on_update = f; }
};

template <std::size_t nb_button, typename ValueT>
class RadioButton: public RadioButtonG<nb_button, Button, ValueT> {
using Base = RadioButtonG<nb_button, Button, ValueT>;
public:
    RadioButton(const sf::String& text, const sf::Font& font, const unsigned int& characterSize = 30U, const int& index_selected_default = 0):
        Base(index_selected_default)
    {
        for (unsigned int i = 0U; i < nb_button; i++) {
            this->operator[](i).button.setString(text);
            this->operator[](i).button.setFont(font);
            this->operator[](i).button.setCharacterSize(characterSize);
        }
    }

    RadioButton(const sf::Font& font, const unsigned int& characterSize = 30U, const int& index_selected_default = 0):
        RadioButton("", font, characterSize, index_selected_default) {}
};
