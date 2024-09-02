# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk

import unittest

class ColorTest(unittest.TestCase):

    def test_members(self):
        c1 = dtk.Color1F()
        self.assertEqual(c1[0], 0)
        c2 = dtk.Color2F()
        self.assertEqual(c2[0], 0)
        self.assertEqual(c2[1], 0)
        c3 = dtk.Color3F()
        self.assertEqual(c3[0], 0)
        self.assertEqual(c3[1], 0)
        self.assertEqual(c3[2], 0)
        c4 = dtk.Color4F()
        self.assertEqual(c4[0], 0)
        self.assertEqual(c4[1], 0)
        self.assertEqual(c4[2], 0)
        self.assertEqual(c4[3], 0)
        
        c1 = dtk.Color1F(1)
        self.assertEqual(c1.l, 1)
        c2 = dtk.Color2F(1, 1)
        self.assertEqual(c2.l, 1)
        self.assertEqual(c2.a, 1)
        c3 = dtk.Color3F(1, 1, 1)
        self.assertEqual(c3.r, 1)
        self.assertEqual(c3.g, 1)
        self.assertEqual(c3.b, 1)
        c4 = dtk.Color4F(1, 1, 1, 1)
        self.assertEqual(c4.r, 1)
        self.assertEqual(c4.g, 1)
        self.assertEqual(c4.b, 1)
        self.assertEqual(c4.a, 1)

        c1 = dtk.Color1F()
        c1[0] = 1
        self.assertEqual(c1[0], 1)
        c2 = dtk.Color2F()
        c2[0] = 1
        self.assertEqual(c2[0], 1)
        c3 = dtk.Color3F()
        c3[0] = 1
        self.assertEqual(c3[0], 1)
        c4 = dtk.Color4F()
        c4[0] = 1
        self.assertEqual(c4[0], 1)

    def test_operators(self):
        self.assertEqual(dtk.Color1F(1), dtk.Color1F(1))
        self.assertNotEqual(dtk.Color1F(1), dtk.Color1F(0))
