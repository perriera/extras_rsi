/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { EtymologyComponent } from './etymology.component';

describe('EtymologyComponent', () => {
  let component: EtymologyComponent;
  let fixture: ComponentFixture<EtymologyComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ EtymologyComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(EtymologyComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

