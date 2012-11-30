/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */

#ifndef STORABLEINTERFACE_H
#define STORABLEINTERFACE_H

#include <QString>
#include <QList>
#include <QMap>
#include <QVariant>


/*
  The storable interface is responsible for providing
  an interface through which implementing objects can
  provide metadata about themselves. Each object that
  wishes to be stored or sent across the network will
  implement this interface and say what attributes
  they have and what are the values of those
  attributes. The interface also provides the ability
  for an object to tell the world what type it is.

  All methods of this protocol MUST be implemented by
  any implementing class.

  */

class StorableInterface
{
public:
    /*
       This method allows the implementing object to
       specify the name of each of it's attributes
       and also the values that correspond to each
       of those attributes.

             attributesAndValues - Output parameter
             that allows the implementing object to
             fill the QMap with the corresponding
             attribute names and their corresponding
             values
      */
    virtual void getAttributesAndValues(QMap<QString, QVariant> & attributesAndValues) const = 0;
    /*
       This method allows the implementing object
       to be constructed from a map of attributes
       and values.

             attributesAndValues - Input parameter
             that allows the implementing object to
             be made to reflect the given
             attributes and values.
      */
    virtual void setAttributesAndValues(const QMap<QString, QVariant> & attributesAndValues) = 0;
    /*
        This method allows the implementing object
        to specify what type it is by giving a name
        that corresponds to all of the objects of
        that type. This value is used by the
        factory in the end to figure out what type
        of object to construct
      */
    virtual QString className() const =0;
    /*
      This method allows the implementing object to
      specify what key of the attributes should be
      used as the unique identifier for the object
      */
    virtual QString getIdentifierKey() const = 0;

    virtual ~StorableInterface() {};


};

#endif // STORABLEINTERFACE_H
