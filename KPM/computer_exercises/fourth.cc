/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * @Author Alex Sporni
 * @Date 15.11.2020
 */

// necessary includes
#include "ns3/object.h"
#include "ns3/uinteger.h"
#include "ns3/traced-value.h"
#include "ns3/trace-source-accessor.h"

#include <iostream>

using namespace ns3; // ns3 namespace declaration

// creating a public class MyObject
class MyObject : public Object
{
public:
  /**
   * Register this type.
   * \return The TypeId.
   */

  // public static function with a name TypeId, wihout parameters
  static TypeId GetTypeId (void)
  {
      // creating a static object of type TypeId
    static TypeId tid = TypeId ("MyObject")
      .SetParent<Object> () // setting up the parent
      .SetGroupName ("Tutorial")    // setting up the GroupName to tutorial
      .AddConstructor<MyObject> ()  // creating a constructor
      .AddTraceSource ("MyInteger", // creating a tracesource MyInteger
                       "An integer value to trace.",
                       MakeTraceSourceAccessor (&MyObject::m_myInt),
                       "ns3::TracedValueCallback::Int32")
    ;
    return tid; // return value
  }

  MyObject () {} // constructor
  TracedValue<int32_t> m_myInt; //32b integer in the object tracedValue
};

// Function Inttrace without a returning parameter, this function is used to print to stdout
void IntTrace (int32_t oldValue, int32_t newValue)
{
  std::cout << "Traced " << oldValue << " to " << newValue << std::endl;
}

// the main function of the program
int main (int argc, char *argv[])
{
    // creating an object myObject through a constructor
  Ptr<MyObject> myObject = CreateObject<MyObject> ();
  myObject->TraceConnectWithoutContext ("MyInteger", MakeCallback (&IntTrace));
    // assigning the integer value 1234 to the object m_myInt
  myObject->m_myInt = 1234;
}
