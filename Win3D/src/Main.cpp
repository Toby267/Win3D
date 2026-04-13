#include "Application.hpp"
#include "engine/Engine.hpp"

//Driver code
int main(int argc, char *argv[]) {
    Engine e = Engine(400, 400);
    Application app = Application(e);

    return 0;
}
