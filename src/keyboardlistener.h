#ifndef KEYBOARDLISTENER_H_INCLUDED
#define KEYBOARDLISTENER_H_INCLUDED

#include "inputlistenerobserver.h"
#include "command.h"


class KeyboardListener {
public:
  KeyboardListener();
  
  ~KeyboardListener();

  void subscribe(
    InputListenerObserver* observer,
    void (InputListenerObserver::*observerFunction)(MovePlayerCommand command)
  );

private:
};


#endif // KEYBOARDLISTENER_H_INCLUDED