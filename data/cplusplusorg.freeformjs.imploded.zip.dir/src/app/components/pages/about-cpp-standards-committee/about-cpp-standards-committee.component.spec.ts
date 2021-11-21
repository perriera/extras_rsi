/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { AboutCppStandardsCommitteeComponent } from './about-cpp-standards-committee.component';

describe('AboutCppStandardsCommitteeComponent', () => {
  let component: AboutCppStandardsCommitteeComponent;
  let fixture: ComponentFixture<AboutCppStandardsCommitteeComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ AboutCppStandardsCommitteeComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(AboutCppStandardsCommitteeComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

