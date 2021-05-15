; Auto-generated. Do not edit!


(cl:in-package question_one-msg)


;//! \htmlinclude Input.msg.html

(cl:defclass <Input> (roslisp-msg-protocol:ros-message)
  ((coor
    :reader coor
    :initarg :coor
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0))
   (angels
    :reader angels
    :initarg :angels
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0))
   (d
    :reader d
    :initarg :d
    :type cl:integer
    :initform 0))
)

(cl:defclass Input (<Input>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Input>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Input)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name question_one-msg:<Input> is deprecated: use question_one-msg:Input instead.")))

(cl:ensure-generic-function 'coor-val :lambda-list '(m))
(cl:defmethod coor-val ((m <Input>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader question_one-msg:coor-val is deprecated.  Use question_one-msg:coor instead.")
  (coor m))

(cl:ensure-generic-function 'angels-val :lambda-list '(m))
(cl:defmethod angels-val ((m <Input>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader question_one-msg:angels-val is deprecated.  Use question_one-msg:angels instead.")
  (angels m))

(cl:ensure-generic-function 'd-val :lambda-list '(m))
(cl:defmethod d-val ((m <Input>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader question_one-msg:d-val is deprecated.  Use question_one-msg:d instead.")
  (d m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Input>) ostream)
  "Serializes a message object of type '<Input>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'coor))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'coor))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'angels))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'angels))
  (cl:let* ((signed (cl:slot-value msg 'd)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Input>) istream)
  "Deserializes a message object of type '<Input>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'coor) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'coor)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296)))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'angels) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'angels)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296)))))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'd) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Input>)))
  "Returns string type for a message object of type '<Input>"
  "question_one/Input")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Input)))
  "Returns string type for a message object of type 'Input"
  "question_one/Input")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Input>)))
  "Returns md5sum for a message object of type '<Input>"
  "3be8f3c7ed7c714a63dc54684d742471")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Input)))
  "Returns md5sum for a message object of type 'Input"
  "3be8f3c7ed7c714a63dc54684d742471")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Input>)))
  "Returns full string definition for message of type '<Input>"
  (cl:format cl:nil "int32[] coor ~%int32[] angels ~%int32 d~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Input)))
  "Returns full string definition for message of type 'Input"
  (cl:format cl:nil "int32[] coor ~%int32[] angels ~%int32 d~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Input>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'coor) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'angels) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Input>))
  "Converts a ROS message object to a list"
  (cl:list 'Input
    (cl:cons ':coor (coor msg))
    (cl:cons ':angels (angels msg))
    (cl:cons ':d (d msg))
))
