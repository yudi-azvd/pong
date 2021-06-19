#ifndef INPUTLISTENEROBSERVER_H_INCLUDED
#define INPUTLISTENEROBSERVER_H_INCLUDED


class InputListenerObserver {
public:
  virtual ~InputListenerObserver() {};

  virtual void handleInput() = 0;
};


#endif // INPUTLISTENEROBSERVER_H_INCLUDED