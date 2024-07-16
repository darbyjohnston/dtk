# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk.dtkCore as dtk

import unittest

class VectorTest(unittest.TestCase):

    def test_members(self):
        v2 = dtk.V2I()
        self.assertEqual(v2[0], 0)
        self.assertEqual(v2[1], 0)
        v3 = dtk.V3F()
        self.assertEqual(v3[0], 0)
        self.assertEqual(v3[1], 0)
        self.assertEqual(v3[2], 0)
        v4 = dtk.V4F()
        self.assertEqual(v4[0], 0)
        self.assertEqual(v4[1], 0)
        self.assertEqual(v4[2], 0)
        self.assertEqual(v4[3], 0)
        
        v2 = dtk.V2I()
        v2[0] = 1
        v2[1] = 2
        self.assertEqual(v2[0], 1)
        self.assertEqual(v2[1], 2)
        v3 = dtk.V3F()
        v3[0] = 1
        v3[1] = 2
        v3[2] = 3
        self.assertEqual(v3[0], 1)
        self.assertEqual(v3[1], 2)
        self.assertEqual(v3[2], 3)
        v4 = dtk.V4F()
        v4[0] = 1
        v4[1] = 2
        v4[2] = 3
        v4[3] = 4
        self.assertEqual(v4[0], 1)
        self.assertEqual(v4[1], 2)
        self.assertEqual(v4[2], 3)
        self.assertEqual(v4[3], 4)
        
        v2 = dtk.V2I(1, 2)
        self.assertEqual(v2.x, 1)
        self.assertEqual(v2.y, 2)
        v3 = dtk.V3F(1, 2, 3)
        self.assertEqual(v3.x, 1)
        self.assertEqual(v3.y, 2)
        self.assertEqual(v3.z, 3)
        v4 = dtk.V4F(1, 2, 3, 4)
        self.assertEqual(v4.x, 1)
        self.assertEqual(v4.y, 2)
        self.assertEqual(v4.z, 3)
        self.assertEqual(v4.w, 4)
        
        v2 = dtk.V2I()
        v2.x = 1;
        v2.y = 2;
        self.assertEqual(v2.x, 1)
        self.assertEqual(v2.y, 2)
        v3 = dtk.V3F()
        v3.x = 1
        v3.y = 2
        v3.z = 3
        self.assertEqual(v3.x, 1)
        self.assertEqual(v3.y, 2)
        self.assertEqual(v3.z, 3)
        v4 = dtk.V4F()
        v4.x = 1
        v4.y = 2
        v4.z = 3
        v4.w = 4
        self.assertEqual(v4.x, 1)
        self.assertEqual(v4.y, 2)
        self.assertEqual(v4.z, 3)
        self.assertEqual(v4.w, 4)

    def test_functions(self):
        l = dtk.length(dtk.V2F(0, 1))
        self.assertEqual(1, l)
        l = dtk.length(dtk.V2F(1, 0))
        self.assertEqual(1, l)
        
        v = dtk.normalize(dtk.V2F(0, 2))
        self.assertEqual(dtk.length(v), 1)
        v = dtk.normalize(dtk.V2F(2, 0))
        self.assertEqual(dtk.length(v), 1)
        
        d = dtk.dot(dtk.V2F(0, 1), dtk.V2F(1, 0))
        self.assertEqual(0, d)
        d = dtk.dot(dtk.V2F(0, 1), dtk.V2F(0, -1))
        self.assertEqual(-1, d)
        
        v = dtk.perpCW(dtk.V2F(1, 0))
        self.assertEqual(dtk.V2F(0, -1), v)
        v = dtk.perpCCW(dtk.V2F(1, 0))
        self.assertEqual(dtk.V2F(0, 1), v)

    def test_operators(self):
        v = dtk.V2F(1, 2) + dtk.V2F(3, 4)
        self.assertEqual(dtk.V2F(4, 6), v)
        v = dtk.V2F(1, 2) + 1
        self.assertEqual(dtk.V2F(2, 3), v)

        v = dtk.V2F(3, 4) - dtk.V2F(1, 2)
        self.assertEqual(dtk.V2F(2, 2), v)
        v = dtk.V2F(3, 4) - 1
        self.assertEqual(dtk.V2F(2, 3), v)
        
        self.assertEqual(dtk.V2F(1, 2), dtk.V2F(1, 2))
        self.assertNotEqual(dtk.V2F(1, 2), dtk.V2F(2, 1))
