#include <iostream>
#include <fstream>

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref

std::ofstream g_file;
std::string g_input;
int main(void) {
  using namespace ftxui;
  using namespace std;

  // init
  g_file.open("1.log");
  g_file << "start\n";
  g_file.flush();
  InputOption option;
    option.on_enter = [&]() {
      g_file << "press enter\n";
      g_file.flush();
    };
    Component input_key_words =
        Input(&g_input, "input words", option);

    auto component = Container::Vertical({
        input_key_words,
    });

    auto renderer = Renderer(component, [&] {
      
      return vbox({
                 hbox(text(" Search : "), input_key_words->Render()),
                 separator(),
             }) |
             border;
    });



    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);
  g_file.close();
  return EXIT_SUCCESS;
}
