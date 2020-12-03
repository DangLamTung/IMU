# Code adapted from Tensorflow Object Detection Framework
# https://github.com/tensorflow/models/blob/master/research/object_detection/object_detection_tutorial.ipynb
# Tensorflow Object Detection Detector

import numpy as np
import tensorflow.compat.v1 as tf
import cv2
import time


class DetectorAPI:
    def __init__(self, path_to_ckpt):
        self.path_to_ckpt = path_to_ckpt
        
        self.detection_graph = tf.Graph()
        with self.detection_graph.as_default():
            od_graph_def = tf.GraphDef()
            with tf.gfile.GFile(self.path_to_ckpt, 'rb') as fid:
                serialized_graph = fid.read()
                od_graph_def.ParseFromString(serialized_graph)
                tf.import_graph_def(od_graph_def, name='')

        self.default_graph = self.detection_graph.as_default()
        self.sess = tf.Session(graph=self.detection_graph)

        # Definite input and output Tensors for detection_graph
        self.image_tensor = self.detection_graph.get_tensor_by_name('image_tensor:0')
        # Each box represents a part of the image where a particular object was detected.
        self.detection_boxes = self.detection_graph.get_tensor_by_name('detection_boxes:0')
        # Each score represent how level of confidence for each of the objects.
        # Score is shown on the result image, together with the class label.
        self.detection_scores = self.detection_graph.get_tensor_by_name('detection_scores:0')
        self.detection_classes = self.detection_graph.get_tensor_by_name('detection_classes:0')
        self.num_detections = self.detection_graph.get_tensor_by_name('num_detections:0')

    def processFrame(self, image):
        # Expand dimensions since the trained_model expects images to have shape: [1, None, None, 3]
        image_np_expanded = np.expand_dims(image, axis=0)
        # Actual detection.
        start_time = time.time()
        (boxes, scores, classes, num) = self.sess.run(
            [self.detection_boxes, self.detection_scores, self.detection_classes, self.num_detections],
            feed_dict={self.image_tensor: image_np_expanded})
        end_time = time.time()

        print("Elapsed Time:", end_time-start_time)

        im_height, im_width,_ = image.shape
        boxes_list = [None for i in range(boxes.shape[1])]
        for i in range(boxes.shape[1]):
            boxes_list[i] = (int(boxes[0,i,0] * im_height),
                        int(boxes[0,i,1]*im_width),
                        int(boxes[0,i,2] * im_height),
                        int(boxes[0,i,3]*im_width))

        return boxes_list, scores[0].tolist(), [int(x) for x in classes[0].tolist()], int(num[0])

    def close(self):
        self.sess.close()
        self.default_graph.close()
count = [0]
pre_pos = []
def check_point(point_list,update):
    temp = point_list.copy()
    global count, pre_pos
    if((len(temp) == 0)& (len(update) > 0)):
        temp = update.copy()
        count.append(0)
    for (i,next_pos) in enumerate(update):
        for (j,current_pos) in enumerate(point_list):
            if( (abs(next_pos[0] - current_pos[0]) < 30) & (abs(next_pos[1] - current_pos[1]) < 30)):
                temp[j] = next_pos
            else:
                if(len(temp) < len(update)):
                    temp.append(next_pos)
                    count.append(0)
    while(len(temp) > len(count)):
        count.append(0)
    if(len(pre_pos) != 0):
        for (j,pos) in enumerate(temp):
            if(count[j] != 0):
                if(len(pre_pos) > j):
                    pre_data = pre_pos[j] 
                    if( (abs(pre_data[0] - pos[0]) == 0) & (abs(pre_data[1] - pos[1]) == 0)):
                        count[j] += 1  
                    else:
                        count[j] = 1
            else:
                count[j] = 1
        for (i,k) in enumerate(count):
            if(k > 6):
                temp.pop(i)
                count.pop(i)
        temp = list(dict.fromkeys(temp))
    pre_pos = temp.copy()
    return temp
class person:
    def __init__(self, position):
        self.position = position
        self.check = False
        self.dir = 0
        self.out = False
        self.count = 0
    def update(pos):
        if ( pos[1] - self.position[1] < 0):
            self.dir = -1
        elif( pos[1] - self.position[1] != 0):
            self.dir = 1
        self.position = pos
if __name__ == "__main__":
    tf.disable_v2_behavior()
    model_path = './fast/frozen_inference_graph.pb'
    odapi = DetectorAPI(path_to_ckpt=model_path)
    threshold = 0.4
    cap = cv2.VideoCapture('./pedestrian.mp4')
    data = []
    up = 0
    down = 0
    fps = 20
    check = True
    human_list = {}
    pre_human_list = []
    
    check_update = []
    font = cv2.FONT_HERSHEY_SIMPLEX 
  
    # org 
    org = (50, 50) 
    org1 = (50, 80)
    # fontScale 
    fontScale = 1
    
    # Blue color in BGR 
    color = (255, 0, 0) 
    
    # Line thickness of 2 px 
    thickness = 2
    tracking = []

    out = cv2.VideoWriter("./video1.mp4",cv2.VideoWriter_fourcc(*'DIVX'), fps, (1280, 720))
    while True:
        r, img = cap.read()
        img = cv2.resize(img, (1280, 720))
        
        boxes, scores, classes, num = odapi.processFrame(img)

        # Visualization of the results of a detection.
        center = []
        for i in range(len(boxes)):
            # Class 1 represents human
            if classes[i] == 1 and scores[i] > threshold:
                box = boxes[i]
                cv2.rectangle(img,(box[1],box[0]),(box[3],box[2]),(255,0,0),2)
                point = (int((box[1] + box[3])/2),int((box[0] + box[2])/2))
                image = cv2.circle(img,point, 5, (255,0,0), 5) 
                center.append(point)
        if((len(center)!=0) & check):
            check = False
        human_list = center.copy()
        human_list = check_point(human_list,center)
        while ((len(check_update) < len(human_list))):
            check_update.append(0)
        human_list = sorted(human_list, key=lambda tup: tup[0])
        for (i,next_pos) in enumerate(human_list):
            for (j,current_pos) in enumerate(pre_human_list):
                if( (abs(next_pos[0] - current_pos[0]) < 30) & (abs(next_pos[1] - current_pos[1]) < 30)):

                    
                    if( (( next_pos[1] - current_pos[1]) < 0) & (next_pos[1] <500)):
                        up += 1

                    if( (( next_pos[1] - current_pos[1]) > 0) & (next_pos[1] >400) &(current_pos[1] <400)):
                        down += 1

        print(tracking)
        print(pre_human_list)
        # pre_check_update = check_update.copy()

        pre_human_list = human_list.copy()
        print(up, down)
        image = cv2.putText(img, 'Up: ' + str(up) , org, font,fontScale, color, thickness, cv2.LINE_AA) 
        image = cv2.putText(img, 'Down: ' + str(down), org1, font,fontScale, (0, 0, 255) , thickness, cv2.LINE_AA) 
        cv2.line(img,(1280,400),(0,400),(0,0,255),2)
        cv2.line(img,(1280,500),(0,500),(255,0,0),2)
        out.write(img)
        cv2.imshow("preview", img)
        key = cv2.waitKey(1)
        if key & 0xFF == ord('q'):
            out.release()
            break

