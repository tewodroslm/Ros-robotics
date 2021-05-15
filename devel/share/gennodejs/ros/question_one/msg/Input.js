// Auto-generated. Do not edit!

// (in-package question_one.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Input {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.coor = null;
      this.angels = null;
      this.d = null;
    }
    else {
      if (initObj.hasOwnProperty('coor')) {
        this.coor = initObj.coor
      }
      else {
        this.coor = [];
      }
      if (initObj.hasOwnProperty('angels')) {
        this.angels = initObj.angels
      }
      else {
        this.angels = [];
      }
      if (initObj.hasOwnProperty('d')) {
        this.d = initObj.d
      }
      else {
        this.d = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Input
    // Serialize message field [coor]
    bufferOffset = _arraySerializer.int32(obj.coor, buffer, bufferOffset, null);
    // Serialize message field [angels]
    bufferOffset = _arraySerializer.int32(obj.angels, buffer, bufferOffset, null);
    // Serialize message field [d]
    bufferOffset = _serializer.int32(obj.d, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Input
    let len;
    let data = new Input(null);
    // Deserialize message field [coor]
    data.coor = _arrayDeserializer.int32(buffer, bufferOffset, null)
    // Deserialize message field [angels]
    data.angels = _arrayDeserializer.int32(buffer, bufferOffset, null)
    // Deserialize message field [d]
    data.d = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 4 * object.coor.length;
    length += 4 * object.angels.length;
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'question_one/Input';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3be8f3c7ed7c714a63dc54684d742471';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32[] coor 
    int32[] angels 
    int32 d
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Input(null);
    if (msg.coor !== undefined) {
      resolved.coor = msg.coor;
    }
    else {
      resolved.coor = []
    }

    if (msg.angels !== undefined) {
      resolved.angels = msg.angels;
    }
    else {
      resolved.angels = []
    }

    if (msg.d !== undefined) {
      resolved.d = msg.d;
    }
    else {
      resolved.d = 0
    }

    return resolved;
    }
};

module.exports = Input;
