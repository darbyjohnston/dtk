# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import tinygfx.tgCore as tg

import unittest

class SizeTest(unittest.TestCase):

    def test_members(self):
        s2 = tg.Size2I()
        self.assertEqual(s2[0], 0)
        self.assertEqual(s2[1], 0)
        self.assertFalse(s2.valid)
        s3 = tg.Size3F()
        self.assertEqual(s3[0], 0)
        self.assertEqual(s3[1], 0)
        self.assertEqual(s3[2], 0)
        self.assertFalse(s3.valid)
        
        s2 = tg.Size2I(1, 2)
        self.assertEqual(s2.w, 1)
        self.assertEqual(s2.h, 2)
        s3 = tg.Size3F(1, 2, 3)
        self.assertEqual(s3.w, 1)
        self.assertEqual(s3.h, 2)
        self.assertEqual(s3.d, 3)
        
        s2 = tg.Size2I()
        s2[0] = 1
        s2[1] = 2
        self.assertEqual(s2[0], 1)
        self.assertEqual(s2[1], 2)
        s3 = tg.Size3F()
        s3[0] = 1
        s3[1] = 2
        s3[2] = 3
        self.assertEqual(s3[0], 1)
        self.assertEqual(s3[1], 2)
        self.assertEqual(s3[2], 3)

    def test_functions(self):
        s2 = tg.Size2I(2, 1)
        self.assertEqual(2, tg.aspectRatio(s2))
        s2 = tg.Size2F(2, 1)
        self.assertEqual(2, tg.aspectRatio(s2))
        
        s2 = tg.Size2F(1, 2)
        self.assertEqual(2, tg.area(s2))
        
        s3 = tg.Size3F(1, 2, 3)
        self.assertEqual(6, tg.volume(s3))

    def test_operators(self):
        s2 = tg.Size2I(1, 2)
        s2a = s2 + 1
        s2b = s2 - 1
        self.assertEqual(tg.Size2I(2, 3), s2a)
        self.assertEqual(tg.Size2I(0, 1), s2b)

        self.assertEqual(tg.Size2I(1, 2), tg.Size2I(1, 2))
        self.assertNotEqual(tg.Size2I(1, 2), tg.Size2I(2, 1))
