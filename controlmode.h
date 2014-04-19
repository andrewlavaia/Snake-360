
#ifndef CONTROLMODE_H
#define CONTROLMODE_H

#include <string>

class ControlMode
{
public:
  ControlMode(std::string type="keyboard");

  std::string getControlType() { return controltype; };

  void setControlType(std::string type) { this->controltype = type; };

private:
  std::string controltype;

};


#endif

