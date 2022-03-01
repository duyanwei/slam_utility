#!/usr/bin/env python
# -*-coding:utf-8 -*-
'''
@file parsing.py
@author Yanwei Du (duyanwei0702@gmail.com)
@date 03-01-2022
@version 1.0
@license Copyright (c) 2022
@desc None
'''

import glob
import os
import shutil
import zipfile

def unzip_dataset(input_dirs):
    dataset = os.path.join(input_dirs, 'Images.zip')
    with zipfile.ZipFile(dataset, 'r') as zip_ref:
        zip_ref.extractall(input_dirs)

def process(input_dirs):
    files = sorted(glob.glob(os.path.join(input_dirs, 'Images/*.jpg')))
    print('files size = {}'.format(len(files)))
    dividing(input_dirs, files, 'left')
    dividing(input_dirs, files, 'right')
    appending(input_dirs, files, 'append')


def dividing(input_dirs, files, data_type):
    output_dirs = os.path.join(input_dirs, data_type)
    print('output dir = {}'.format(output_dirs))

    if not os.path.exists(output_dirs):
        os.makedirs(output_dirs)

    start_idx = 0 if data_type == 'left' else 1
    count = 0
    for i in range(start_idx, len(files), 2):
        count += 1
        output = os.path.join(output_dirs, str(count).zfill(4) + '.jpg')
        shutil.copyfile(files[i], output)
    print('processed {} images in {}'.format(count, data_type))

def appending(input_dirs, files, data_type):
    output_dirs = os.path.join(input_dirs, data_type)
    print('output dir = {}'.format(output_dirs))

    if not os.path.exists(output_dirs):
        os.makedirs(output_dirs)

    count = 0
    for i in range(0, len(files), 2):
        left = files[i]
        right = files[i+1]
        count += 1
        output = os.path.join(output_dirs, str(count).zfill(4) + '.jpg')
        cmd = 'convert ' + left + ' ' + right + ' +append' + ' ' + output
        os.system(cmd)
    print('processed {} images in {}'.format(count, data_type))

def parsing(input_dirs):
    unzip_dataset(input_dirs)
    process(input_dirs)
    # shutil.rmtree(os.path.join(input_dirs, 'Images/'))

def prepare_imagelist_for_MILD(input_dirs, data_type):
    files = sorted(glob.glob(os.path.join(input_dirs, data_type, '*.jpg')))
    output = 'imagelist' + '_' + data_name + '_' + data_type + '.txt'
    output = os.path.join(input_dirs, output)
    print('imagelist for MILD output = {}'.format(output))

    with open(output, 'w') as f:
        f.writelines('\n'.join(files))

if __name__ == '__main__':

    # setting variables
    prefix = '/home/duyanwei/data/'
 #   data_name = 'NewCollege2008' # CityCentre
    data_name =  'CityCentre'

    # preset variables
    input_dirs = os.path.join(prefix, data_name)
    print('input dir = {}'.format(input_dirs))

    # start parsing
    parsing(input_dirs)

    ## preparing dataset for MILD
    # prepare_imagelist_for_MILD(input_dirs, 'left')
    # prepare_imagelist_for_MILD(input_dirs, 'right')
    # prepare_imagelist_for_MILD(input_dirs, 'append')