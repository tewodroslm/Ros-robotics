;; Auto-generated. Do not edit!


(when (boundp 'question_one::Input)
  (if (not (find-package "QUESTION_ONE"))
    (make-package "QUESTION_ONE"))
  (shadow 'Input (find-package "QUESTION_ONE")))
(unless (find-package "QUESTION_ONE::INPUT")
  (make-package "QUESTION_ONE::INPUT"))

(in-package "ROS")
;;//! \htmlinclude Input.msg.html


(defclass question_one::Input
  :super ros::object
  :slots (_coor _angels _d ))

(defmethod question_one::Input
  (:init
   (&key
    ((:coor __coor) (make-array 0 :initial-element 0 :element-type :integer))
    ((:angels __angels) (make-array 0 :initial-element 0 :element-type :integer))
    ((:d __d) 0)
    )
   (send-super :init)
   (setq _coor __coor)
   (setq _angels __angels)
   (setq _d (round __d))
   self)
  (:coor
   (&optional __coor)
   (if __coor (setq _coor __coor)) _coor)
  (:angels
   (&optional __angels)
   (if __angels (setq _angels __angels)) _angels)
  (:d
   (&optional __d)
   (if __d (setq _d __d)) _d)
  (:serialization-length
   ()
   (+
    ;; int32[] _coor
    (* 4    (length _coor)) 4
    ;; int32[] _angels
    (* 4    (length _angels)) 4
    ;; int32 _d
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32[] _coor
     (write-long (length _coor) s)
     (dotimes (i (length _coor))
       (write-long (elt _coor i) s)
       )
     ;; int32[] _angels
     (write-long (length _angels) s)
     (dotimes (i (length _angels))
       (write-long (elt _angels i) s)
       )
     ;; int32 _d
       (write-long _d s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32[] _coor
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _coor (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _coor i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;; int32[] _angels
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _angels (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _angels i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;; int32 _d
     (setq _d (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get question_one::Input :md5sum-) "3be8f3c7ed7c714a63dc54684d742471")
(setf (get question_one::Input :datatype-) "question_one/Input")
(setf (get question_one::Input :definition-)
      "int32[] coor 
int32[] angels 
int32 d
")



(provide :question_one/Input "3be8f3c7ed7c714a63dc54684d742471")


