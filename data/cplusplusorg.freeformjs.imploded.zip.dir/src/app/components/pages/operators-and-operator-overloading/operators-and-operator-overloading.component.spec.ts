/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { OperatorsAndOperatorOverloadingComponent } from './operators-and-operator-overloading.component';

describe('OperatorsAndOperatorOverloadingComponent', () => {
  let component: OperatorsAndOperatorOverloadingComponent;
  let fixture: ComponentFixture<OperatorsAndOperatorOverloadingComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ OperatorsAndOperatorOverloadingComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(OperatorsAndOperatorOverloadingComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

